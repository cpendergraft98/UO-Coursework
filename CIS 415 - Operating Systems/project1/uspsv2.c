/*
 * 	CIS 415 Project 1 Authorship Statement
 * 	Written by Cole Pendergraft, DUCKID: cpenderg
 * 	This is my own work.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "p1fxns.h"
#include <signal.h>

#define MIN_QUANTUM 20
#define MAX_QUANTUM 2000
#define MAXPCBS 512
int quantum = -1;

// Using the PCB struct from lab4 signal.c
typedef struct pcb
{
	pid_t pid;
}PCB;

PCB array[MAXPCBS];

// A helper function to execute the commands in commands array on forked child processes
// commandsarray is an array of command line inputs
// num_proccs is the number of processes to run, should be = to the number of commands
void execute(char **commandsarray,  int num_proccs)
{
	// Create neccessary sigset stuff to halt processes before execution
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	// Instantite PCB
	PCB *pcb;
	// Iterate over the commands in commandsarray
	for(int i = 0; i < num_proccs; i++)
	{	
		// Set pcb
		pcb = array + i;
	    // Fork a child process	
		pid_t pid = fork();
		// Get the status of the fork and decide what to do next
		switch(pid)
		{
			// If our fork fails
			case -1:
				p1perror(2, "Problem with fork()\n");
				exit(EXIT_FAILURE);

			// Time to execute
			case 0: ;

				// Create an array full of null initialized values to store the executable
				// and its arguments separately
				char *execlist[BUFSIZ];
				for(int i = 0; i < BUFSIZ; i++)
				{
					execlist[i] = '\0';
				}


				// Create an index tracker for the execlist
				int index = 0;

				// A value to hold the status of p1getword
				int status = 0;

				// Create a temp variable to store each word
				char temp[BUFSIZ];
				// Populate execlist
				while( (status = p1getword(commandsarray[i], status, temp)) != -1)
				{
					// Add each word to the execution list
					execlist[index] = p1strdup(temp);
					// Iterate our index
					index++;
				}

				// Separate the executable and the list of arguments
				char* executable = execlist[0];
				char** arguments = &execlist[1];

				// Force all signals to wait for SIGUSR1
				int sig;
				sigwait(&sigset, &sig);
				// Execute the programs
				int x = execvp(executable, arguments);

				// Check for execvp issues
				if(x == -1)
				{
					p1perror(2, "Error running a command with execvp()\n");
					exit(EXIT_FAILURE);
				}

				// Free the entries in the execlist
				for(int i = 0; i < BUFSIZ; i++)
				{
					free(execlist[i]);
				}

				break;

			// If neither of the previous occur, add process to PCB
			default:
				pcb->pid = pid;
				break;
		}
	}

	// Send execution signal to each process
	for(int i = 0; i < num_proccs; i++)
	{
		kill(array[i].pid, SIGUSR1);
	}

	// Send stop signal to each process
	for(int i = 0; i < num_proccs; i++)
	{
		kill(array[i].pid, SIGSTOP);
	}

	// Send continue signal to each process
	for(int i = 0; i < num_proccs; i++)
	{
		kill(array[i].pid, SIGCONT);
	}

	// Set up wait loop
	int active_processes = num_proccs;
	while(active_processes > 0)
	{
		wait(NULL);
		active_processes--;
	}	

}	

int main(int argc, char **argv)
{
	// Grab our quantum value from the environment
	char* p;	
	if((p = getenv("USPS_QUANTUM_MSEC")) != NULL)
	{
		quantum = p1atoi(p);
	}
	
	int opt;	
	// Check for quantum flag
	while((opt = getopt(argc, argv, "q:")) != -1)
	{
		switch(opt)
		{
			// If quantum is flagged then we want to update our quantum variable
			// If provided an invalid flag we print an error message and default 
			// to the value stored in USPS_QUANTUM_MSEC
			case 'q':
				quantum = p1atoi(optarg);
				break;
		}
	}

	// If quantum == -1 then the user has attempted to use USPS_QUANTUM_MSEC without defining
	// it.
	// (If the user specifies "-q -1" this check will not error, but the next one will.)
	if(quantum == -1)
	{
		p1perror(2, "Detected attempt to use USPS_QUANTUM_MSEC as quantum value, but USPS_QUANTUM_MSEC not defined in environment! Please define it or specify a custom quantum with -q.\n");
		return EXIT_FAILURE;	
	}

	// Make sure that our quantum value is valid	
	if(quantum < MIN_QUANTUM || quantum > MAX_QUANTUM)
	{
		p1perror(2, "Unreasonable quantum provided or pulled from the environment, please specificy a quantum value between 20 and 2000 ms.\n");
		return EXIT_FAILURE;
	}

	// Create an array to store our commands
	char *commands[BUFSIZ];

	// Populate our commands list with a bunch of initial null values
	for(int i = 0; i < BUFSIZ; i++)
	{
		commands[i] = '\0';
	}
	
	// Create a character buffer
	char buf[BUFSIZ];
	// Create an index variable for the commands list
	int cmdind=0;
	// If the argument stored at optind after the check is NULL, then we have no file passed
	if(argv[optind] != (char*)NULL)
	{	
		
		// Open our file and set it to a file descriptor
		int workload = open(argv[optind], O_RDONLY);

		// Now we load the lines from the file into the commands list
		while(p1getline(workload, buf, BUFSIZ) != 0)
		{
			// First, we need to replace the newline character in buf with a 
			// termination character.
			buf[p1strchr(buf, '\n')] = '\0';

			// Now add the buffer into the command list at the cmdind index
			commands[cmdind] = p1strdup(buf);

			// Iterate our cmdind index
			cmdind++;
		
		}
		// When we finish loading our commands, we can close the file.
		close(workload);
			
	}
	else
	{
		char *msg = "No file provided, enter your commands in stdin and press ctrl+d on a new line to execute\n";
		write(0, msg, p1strlen(msg));

		// 0 as a file descriptor represents stdin
		while(p1getline(0, buf, BUFSIZ) != 0)
		{	

			// First, we need to replace the newline character in buf with a 
			// termination character.
			buf[p1strchr(buf, '\n')] = '\0';

			// Now add the buffer into the command list at the cmdind index
			commands[cmdind] = p1strdup(buf);
		
			// Iterate our cmdind index
			cmdind++;

		}
	}

	// Now we call our helper function to execute the commands according to our signals
	execute(commands, cmdind);

	// Free the commands array
	for(int i = 0; i < cmdind; i++)
	{
		free(commands[i]);
	}

	return EXIT_SUCCESS;

}
