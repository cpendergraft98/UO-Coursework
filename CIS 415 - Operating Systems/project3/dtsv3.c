/*
	CIS 415 Project 3, Part 3
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

// Copy of my dtsv2 receieve function with changed/added lines commented
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
		char *queryCopy = strdup(query);

		char *token = strtok(queryCopy, "|"); 
		char *array[BUFSIZ]; 
		int i = 0; 

		while(token != NULL)
		{
			array[i] = token;
			token = strtok(NULL, "|");
			i++;
		}

		if((strcmp(array[0], "OneShot")) == 0) 
		{
			if(i == 7)
			{
				if((strcmp(array[6], "\n")) == 0)
				{
					sprintf(response, "0");
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
				else
				{
					sprintf(response, "1%s", query);
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
			}
			else
			{
				sprintf(response, "0");
				rlen = strlen(response) + 1;
				assert(bxp_response(svc, &ep, response, rlen));
			}
		}
		else if((strcmp(array[0], "Repeat")) == 0)
		{
			if(i == 7)
			{
				if((strcmp(array[6], "\n")) == 0)
				{
					sprintf(response, "0");
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
				else
				{
					sprintf(response, "1%s", query);
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
			}
			else
			{
				sprintf(response, "0");
				rlen = strlen(response) + 1;
				assert(bxp_response(svc, &ep, response, rlen));
			}
		}
		else if((strcmp(array[0], "Cancel")) == 0)
		{
			if(i == 2)
			{
				if((strcmp(array[1], "\n")) == 0)
				{
					sprintf(response, "0");
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
				else
				{
					sprintf(response, "1%s", query);
					rlen = strlen(response) + 1;
					assert(bxp_response(svc, &ep, response, rlen));
				}
			}
			else
			{
				sprintf(response, "0");
				rlen = strlen(response) + 1;
				assert(bxp_response(svc, &ep, response, rlen));
			}
		}
		else
		{
			sprintf(response, "0");
			rlen = strlen(response) + 1;
			assert(bxp_response(svc, &ep, response, rlen));
		}
		free(token);
		free(queryCopy);
		VALGRIND_MONITOR_COMMAND("leak_check summary");
	}
	VALGRIND_MONITOR_COMMAND("leak_check summary");
	return NULL;
}

// Main from dtsv2 with changed/added lines commented
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