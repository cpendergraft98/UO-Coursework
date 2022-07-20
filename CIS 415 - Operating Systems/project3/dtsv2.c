/*
	CIS 415 Project 3, Part 2
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

#define PORT 19999

// Copy of my dtsv1 receive with changes made to the inner while loop to 
// handle parsing of queries. Changed/added lines are commented.
void* receive(UNUSED void* args)
{
	BXPEndpoint ep;
	BXPService svc;

	char query[BUFSIZ], response[BUFSIZ+1];
	unsigned qlen, rlen;
	int port;

	port = PORT;
	assert(bxp_init(port, 1));
	assert((svc = bxp_offer("DTS")));

	VALGRIND_MONITOR_COMMAND("leak_check summary");

	while((qlen = bxp_query(svc, &ep, query, BUFSIZ)) > 0)
	{
		// Basic string tokenization logic from 
		// https://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array

		// Parse requests and set the status byte
		// Create a copy of the query bc strtok will change it
		char *queryCopy = strdup(query);

		char *token = strtok(queryCopy, "|"); // Split query at "|" and tokenize
		char *array[BUFSIZ]; // Initialize array to hold tokens
		int i = 0; // Counter to track number of tokens (arguments)

		// Feed tokens into our token array
		while(token != NULL)
		{
			array[i] = token;
			// Update the new token to be the remaining string once again split at |
			token = strtok(NULL, "|");
			i++;
		}

		// Check the first word in each query to ensure that it
		// is either OneShot, Repeat, or Cancel
		if((strcmp(array[0], "OneShot")) == 0) // If first word is OneShot
		{
			// Make sure there are enough arguments (6 args + the first word)
			if(i == 7)
			{
				// I noticed an edge case with my logic where
				// something like OneShot|x|y|z|w|e| would
				// be considered correct even though it is missing
				// an argument, so we just verify that the last 
				// arg is not a blank space and if it is, we 
				// respond with a status byte of 0
				if((strcmp(array[6], "\n")) == 0) // Inappropriate arg
				{
					// Set status byte to 0 and respond
					sprintf(response, "0");
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
				else // Args are all appropriate
				{
					// If we have enough args then we set the status byte to 1 and respond
					sprintf(response, "1%s", query);
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
			}
			else // We don't have enough args
			{
				// If we don't have enough args the we set the status byte to 0 and respond
				sprintf(response, "0");
				rlen = strlen(response) + 1;
				assert(bxp_response(svc, &ep, response, rlen));
			}
		}
		else if((strcmp(array[0], "Repeat")) == 0) // If first word is Repeat
		{
			// Make sure there are enough arguments (6 args + the first word)
			if(i == 7)
			{
				// Same edge case as previous, inappropriate arg
				if((strcmp(array[6], "\n")) == 0)
				{
					// Set status byte to 0 and respond
					sprintf(response, "0");
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
				else // Args are all appropriate
				{
					// If we have enough args then we set the status byte to 1 and respond
					sprintf(response, "1%s", query);
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
			}
			else // We don't have enough args
			{
				// If we don't have enough args the we set the status byte to 0 and respond
				sprintf(response, "0");
				rlen = strlen(response) + 1;
				assert(bxp_response(svc, &ep, response, rlen));
			}
		}
		else if((strcmp(array[0], "Cancel")) == 0) // If first word is Cancel
		{
			// Make sure there are enough argumetns (1 arg + the first word)
			if(i == 2)
			{
				// Same edge case as previous 2, inappropriate arg
				if((strcmp(array[1], "\n")) == 0)
				{
					// Set status byte to 0 and respond
					sprintf(response, "0");
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
				else // Args are all appropriate
				{
					// If we have enough args then we set the status byte to 1 and respond
					sprintf(response, "1%s", query);
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
			}
			else // We don't have enough args
			{
				// If there are not enough args we set the status byte to 0 and respond
				sprintf(response, "0");
				rlen = strlen(response) + 1;
				assert(bxp_response(svc, &ep, response, rlen));
			}
		}
		else // If first word is not OneShot, Repeat, or Cancel
		{
			// Immediately set the status byte to 0 and respond.
			sprintf(response, "0");
			rlen = strlen(response) + 1;
			assert(bxp_response(svc, &ep, response, rlen));
		}
		// Free the token and queryCopy
		free(token);
		free(queryCopy);
		VALGRIND_MONITOR_COMMAND("leak_check summary");
	}
	VALGRIND_MONITOR_COMMAND("leak_check summary");
	return NULL;
}

// Main is unchanged from dtsv1
int main(UNUSED int argv, UNUSED char **argc)
{
	pthread_t receiver;

	if(pthread_create(&receiver, NULL, &receive, NULL) != 0)
	{
		printf("Faiure to create thread\n");
		return EXIT_FAILURE;
	}

	VALGRIND_MONITOR_COMMAND("leak_check summary");

	pthread_join(receiver, NULL);

	return EXIT_SUCCESS;
}