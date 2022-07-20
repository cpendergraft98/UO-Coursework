/*
	CIS 415 Project 3, Part 1
	Cole Pendergraft, cpenderg, 951544267
This is my own work, but I discussed code logic with Joe Cates and Vladimir Shatalov.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include "BXP/bxp.h"
#include "valgrind/valgrind.h"

#define UNUSED __attribute__((unused))

#define PORT 19999 // Our clients use port 19999

// Pretty much an identical copy of the 5.1.3 BXP Server Example 
// on the project handout. Changed lines are commented
void* receive(UNUSED void* args)
{
	BXPEndpoint ep;
	BXPService svc;

	char query[BUFSIZ], response[BUFSIZ+1]; // Needed response to be BUFSIZ+1 or I error
	unsigned qlen, rlen;
	int port;

	port = PORT;
	assert(bxp_init(port, 1));
	assert((svc = bxp_offer("DTS"))); // We are using DTS, not Echo

	VALGRIND_MONITOR_COMMAND("leak_check summary");

	while((qlen = bxp_query(svc, &ep, query, 10000)) > 0)
	{
		sprintf(response, "1%s", query);
		rlen = strlen(response) + 1;
		assert(bxp_response(svc, &ep, response, rlen));
	}

	VALGRIND_MONITOR_COMMAND("leak_check summary");
	return NULL;
}

int main(UNUSED int argv, UNUSED char **argc)
{
	// Create thread for receiver
	pthread_t receiver;

	// Create pthread and ensure success
	if(pthread_create(&receiver, NULL, &receive, NULL) != 0)
	{
		printf("Faiure to create thread\n");
		return EXIT_FAILURE;
	}

	VALGRIND_MONITOR_COMMAND("leak_check summary");

	// Wait for the thread to finish its job
	pthread_join(receiver, NULL);

	return EXIT_SUCCESS;
}
