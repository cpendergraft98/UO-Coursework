/*
		CIS 415 Project 2
		Name: Cole Pendergraft, DuckID: cpenderg
		This is my own work, but I did discuss code logic with Joe Cates and Thomas Joyce.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "destination.h"
#include "diagnostics.h"
#include "fakeapplications.h"
#include "freepacketdescriptorstore__full.h"
#include "freepacketdescriptorstore.h"
#include "networkdevice__full.h"
#include "networkdevice.h"
#include "packetdescriptorcreator.h"
#include "packetdescriptor.h"
#include "pid.h"
#include "queue.h"
#include "BoundedBuffer.h"

#define UNUSED __attribute__((unused))

// BB to hold PDs ready to be sent to the network
static BoundedBuffer *sendBuf;

// BB to store one BB for each application, with each application BB holding PDs
// that can be sent off to the Application
static BoundedBuffer *bbBuf[MAX_PID + 1];

// BB to store free packet descriptors
static BoundedBuffer *fpdPool;

// Global Store for fpds
static FreePacketDescriptorStore *fpds;

// Global Network Device variable
static NetworkDevice *netDev;

// Threaded function to handle s
void *senderfn(UNUSED void* args)
{
	// PD to hold packet to be sent
	PacketDescriptor *sendPD = NULL;

	while(1)
	{
		// Pull a PD from the sendBuf and place it in the sendPD, blocking until
		// successful
		sendBuf->blockingRead(sendBuf, (void **)&sendPD);

		// Attempt to send packet to the network 10 times, giving up after that many tries.
		int status = 0; // Varible to check if we've succeeded in sending the packet.
		for(int i = 0; i < 10; i++)
		{
			// Attempt to send the PD
			status = netDev->sendPacket(netDev, sendPD);

			// If we succeed, stop trying to send
			if(status == 1)
				break;
		}

		// If status == 0 after loop is done we have failed to send to network, print
		// diagnostic to user
		if(status == 0)
			DIAGNOSTICS("Failed to send packet after 10 tries, giving up...\n");

		// Try to add sendPD to the fpdPool
		if(fpdPool->nonblockingWrite(fpdPool, (void *)sendPD) == 0)
		{
			// If we can't, add it to the FPD store
			fpds->nonblockingPut(fpds, sendPD);
		}
	}
	return NULL;
}

// From Pseudo-code given in Timmy's 5/8 Office Hours
void *getterfn(UNUSED void* args)
{
	// Packet Descriptor to hold the packet to be given to the application
	PacketDescriptor *getPD = NULL;
	// Packet Descriptor to hold the fpd
	PacketDescriptor *fpd = NULL;

	// Get fpd from fpdStore
	fpds->blockingGet(fpds, &fpd);
	// Initialize fpd
	initPD(fpd);
	// Register fpd with the network so the next outgoing packet gets placed into it
	netDev->registerPD(netDev, fpd);

	while(1)
	{
		// Block the thread until a packet is received from the network
		netDev->awaitIncomingPacket(netDev);

		// Set our getPD to the information now stored in the fpd
		getPD = fpd;

		// Value to check the success of nonblockingRead/Get
		int status;

		// Try to pull a fpd from the pool, and if it fails...
		if((status = fpdPool->nonblockingRead(fpdPool, (void **)&fpd)) == 0)
		{
			// ..pull it out of the store instead and store if that was successful
			status = fpds->nonblockingGet(fpds, &fpd);
		}

		// If status == 1 then nonblockingGet/Put succeeded
		if(status == 1)
		{
			// If we can, re-initialize the fpd
			initPD(fpd);

			// Register the fpd with the network to receive the next incoming packet
			netDev->registerPD(netDev, fpd);

			// Get the PID from the getPD to index into bbBuf
			PID pid = getPID(getPD);

			// Try to write the getPD to the bbBuf immediately
			if(bbBuf[pid]->nonblockingWrite(bbBuf[pid], (void *)getPD) == 0)
			{
				// If that fails, attempt to place the now uneeded getPD into the fpdPool
				if(fpdPool->nonblockingWrite(fpdPool, (void *)getPD) == 0)
				{
					// If we can't, block the thread until we can put it in the store
					fpds->blockingPut(fpds, getPD);
				}
			}
		}
		else
		{
			// If status == 0, nonblockingGet/Put failed

			// Set the fpd back equal to the getPD
			fpd = getPD;
			// Re-initialize the fpd
			initPD(fpd);

			// Register the fpd with the network to receive thenext incoming packet
			netDev->registerPD(netDev, fpd);
		}
	}

	return NULL;
}

void init_packet_driver(NetworkDevice *nd, void *mem_start,
	unsigned long mem_length, FreePacketDescriptorStore **fpds_ptr)
{
	// Assign the passed in NetDevice to the global NetDevice variable
	netDev = nd;

	// Initialize FPDS using mem_start and mem_length and obtain its size
	fpds = FreePacketDescriptorStore_create(mem_start, mem_length);
	// Set the passed-in pointer to point to our fpds
	*fpds_ptr = fpds;

	// Create send BB to hold PDs to be sent to the network
	sendBuf = BoundedBuffer_create(10);

	// Create and populate the FPD Pool
	fpdPool = BoundedBuffer_create(4);
	for(int i = 0; i < 4; i++)
	{
		PacketDescriptor *pd = NULL;
		fpds->nonblockingGet(fpds, &pd);
		fpdPool->nonblockingWrite(fpdPool, (void *)pd);
	}

	// Populate bbBuf with empty BBs that will hold PDs ready to be "got" by apps
	for(int i = 0; i < 11; i++)
	{
		bbBuf[i] = BoundedBuffer_create(2);
	}

	// Create and couple threads
	pthread_t sender;
	pthread_t getter;
	pthread_create(&sender, NULL, &senderfn, NULL);
	pthread_create(&getter, NULL, &getterfn, NULL);
}

void blocking_send_packet(PacketDescriptor *pd)
{
	// Queue up packet descriptor for sending
	// Do not end until queued successfully
	sendBuf->blockingWrite(sendBuf, (void *)pd);
}

int nonblocking_send_packet(PacketDescriptor *pd)
{
	// Queue the descriptor immediately. If successful, return 1. If not, return 0;
	return sendBuf->nonblockingWrite(sendBuf, (void *)pd);
}

void blocking_get_packet(PacketDescriptor **pd, PID pid)
{
	// Wait until there is a packet in the queue for PID
	// Send that packet descriptor to the calling app
	bbBuf[pid]->blockingRead(bbBuf[pid], (void**)pd);
}

int nonblocking_get_packet(PacketDescriptor **pd, PID pid)
{
	// If an app has a PD to be got, get it immediately and return 1. Else, return 0.
	return bbBuf[pid]->nonblockingRead(bbBuf[pid], (void**)pd);
}
