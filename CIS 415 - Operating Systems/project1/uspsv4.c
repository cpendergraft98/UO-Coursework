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
#include "ADTs/queue.h"
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#define UNUSED __attribute__((unused))
#define MIN_QUANTUM 20
#define MAX_QUANTUM 2000
#define MAXPCBS 512
#define MS_PER_TICK 20
#define NCURSES_NO_SETBUF true
int quantum = -1;

// Using the PCB struct from lab4 signal.c
typedef struct pcb
{
	pid_t pid;
	int ticks;
	bool isalive;
	bool usr1;
}PCB;

PCB array[MAXPCBS];
volatile int active_processes = 0;
volatile int usr1 = 0;
volatile int usr2 = 0;
int num_procs = 0;
pid_t parent;
const Queue *q = NULL;
PCB *current = NULL;
int ticks_in_quantum = 0;

static void display_info()
{	
	// A variable to hold the pid as a string
	char pidstring[BUFSIZ];
	char *infoprint[BUFSIZ];
	// Iterate over processes 
	for(int i = 0; i < num_procs; i++)
	{
		// Convert pid to a string
		p1itoa(array[i].pid, pidstring);

		// Create /proc/<pid>/stat filepath
		char* statpath = p1strdup("/proc/");
		p1strcat(statpath, pidstring);
		p1strcat(statpath, "/stat");

		// Create /proc/<pid>/io filepath
		char* iopath = p1strdup("/proc/");
		p1strcat(iopath, pidstring);
		p1strcat(iopath, "/io");

		// Open relevant folders for the current process.
		int sf = open(statpath, 0);
		int iof = open(iopath, 0);

		if(sf == -1 || iof == -1)
		{
			return;
		}

		// Create a character string that will hold all of the info to display
		char info[BUFSIZ];

		// Buf to hold stuff from stat file
		char statbuf[BUFSIZ];
		// Add file contents to each buffer
		p1getline(sf, statbuf, BUFSIZ);
		// Grab only relevant information from each line, I use an index tracker to
		// only grab what I want.
		int index = 0;
		// A value to hold the status of p1getword
		int status = 0;
		// Create a temp variable to store each word
		char temp[BUFSIZ];

		// Get from status
		while( (status = p1getword(statbuf, status, temp)) != -1)
		{
			// If index == 0 then we are looking at pid, which we want
			if(index == 0)
			{
				// Cat the word into the info string
				p1strcat(info, temp);
				// Also cat a space into the info string
				p1strcat(info, " ");
				// Increase the index
				index++;
				// Skip to the next loop iteration.
				continue;

			}

			// If index == 1 then we are looking at comm which we want
			if(index == 1)
			{
				// Cat the word into the info string
				p1strcat(info, temp);
				// Also cat a space into the info string
				p1strcat(info, " ");
				// Increase the index
				index++;
				// Skip to the next loop iteration.
				continue;
			}

			// If index == 2 then we are looking at state which we want
			if(index == 2)
			{
				// Cat the word into the info string
				p1strcat(info, temp);
				// Also cat a space into the info string
				p1strcat(info, " ");
				// Increase the index
				index++;
				// Skip to the next loop iteration.
				continue;
			}

			// If index == 3 then we are looking at the parent process
			// which we want
			if(index == 3)
			{
				// Cat the word into the info string
				p1strcat(info, temp);
				// Also cat a space into the info string
				p1strcat(info, " ");
				// Increase the index
				index++;
				// Skip to the next loop iteration.
				continue;
			}

			// If index == 13 we are looking at execution time which we want
			if(index == 13)
			{
				// Cat the word into the info string
				p1strcat(info, temp);
				// Also cat a space into the info string
				p1strcat(info, " ");
				// Increase the index
				index++;
				// Skip to the next loop iteration.
				continue;
			}

			// If index == 22 then we are looking at memory size which we want
			if(index == 22)
			{
				// Cat the word into the info string
				p1strcat(info, temp);
				// Also cat a space into the info string
				p1strcat(info, " ");
				// Increase the index
				index++;
				// Skip to the next loop iteration.
				continue;
			}
			index++;
		}

		// Now for I/O, different logic since entries in proc/pid/io are separated
		// by newlines.
		status = 0;
		index = 0;
		int lineindex = 0;
		char temp1[BUFSIZ];
		char temp2[BUFSIZ];
		while((status = p1getline(iof, temp1, BUFSIZ)) != 0)
		{
			// Make sure to get rid of newline characters
			if(temp1[status-1] == '\n')
			{
				temp1[status-1] = '\t';
			}

			// Get read bytes without the read_bytes tag
			if(lineindex == 2)
			{
				index = p1getword(temp1, 0, temp2);
				p1getword(temp1, index, temp2);
				p1strcat(info, temp2);
				p1strcat(info, " ");
			}

			// Get write bytes without the write_bytes tag
			if(lineindex == 3)
			{
				index = p1getword(temp1, 0, temp2);
				p1getword(temp1, index, temp2);
				p1strcat(info, temp2);
				p1strcat(info, " ");
			}
			lineindex++;
			index = 0;
		}
		p1strcat(info, "\n");
		infoprint[i] = p1strdup(info);
		// Reset the info list for the next iteration
		info[0] = '\0';

		close(sf);
		close(iof);
	}
	char *header = "PID   COMM      S PPID UTIME VSIZE RBYTS WBYTS\n";
	
	p1putstr(1, header);
	for(int i = 0; i < num_procs; i++)
	{
		p1putstr(1, infoprint[i]);
	}
	p1putstr(1, "\n");

}

// From roundrobin.c
static int pid2index(pid_t pid)
{
	int i;
	for(i = 0; i < num_procs; i++)
	{
		if(array[i].pid == pid)
			return i;
	}
	return -1;
}

// From roundrobin.c
static void usr1_handler(UNUSED int sig)
{
	usr1++;
}

// From roundrobin.c
static void	usr2_handler(UNUSED int sig)
{
}

// From JustCh8.pdf + roundrobin.c
static void chld_handler(UNUSED int sig)
{
	pid_t pid;
	int status;

	while((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		if(WIFEXITED(status))
		{
			active_processes--;
			array[pid2index(pid)].isalive = false;
			kill(parent, SIGUSR2);
		}
	}
}

// From roundrobin.c
static void alrm_handler(UNUSED int sig)
{
	if(current != NULL)
	{
		if(current->isalive)
		{	
			current->ticks--;
			if(current->ticks > 0)
			{
				return;
			}
			kill(current->pid, SIGSTOP);
			q->enqueue(q, ADT_VALUE(current));
			display_info();
		}
		current = NULL;
	}

	while(q->dequeue(q, ADT_ADDRESS(&current)))
	{
		if(!current->isalive)
		{
			continue;
		}

		current->ticks = ticks_in_quantum;
		if(current->usr1)
		{
			current->usr1 = false;
			kill(current->pid, SIGUSR1);
		}
		else
		{
			kill(current->pid, SIGCONT);
		}
		return;
	}
}

// A helper function to execute the commands in commands array on forked child processes
// commandsarray is an array of command line inputs
// num_proccs is the number of processes to run, should be = to the number of commands
void execute(char **commandsarray,  int num_proccs)
{

	// Establish parent
	parent = getpid();

	// Tie signals to helpers
	if(signal(SIGUSR1, usr1_handler) == SIG_ERR)
	{
		p1perror(2, "Failed to tie SIGUSR1 to usr1_handler\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGUSR2, usr2_handler) == SIG_ERR)
	{
		p1perror(2, "Failed to tie SIGUSR2 to usr2_handler\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGCHLD, chld_handler) == SIG_ERR)
	{
		p1perror(2, "Failed to tie SIGCHLD to chld_handler\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGALRM, alrm_handler) == SIG_ERR)
	{
		p1perror(2, "Failed to tie SIGALRM to alrm_handler\n");
		exit(EXIT_FAILURE);
	}

	// Create itimer struct
	struct itimerval interval;

	// Create neccessary sigset stuff to halt processes before execution
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigprocmask(SIG_BLOCK, &sigset, NULL);

	// Instantite PCB
	PCB *pcb;
	// Instaniate queue
	q = Queue_create(doNothing);
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

				int x = 0;
				x = execvp(executable, arguments);
			
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
				pcb->isalive = true;
				pcb->usr1 = true;
				q->enqueue(q, ADT_VALUE(pcb));
				break;
		}
		num_procs++; // Iterate value for pid2index
	}

	active_processes = num_proccs;

	interval.it_value.tv_sec = MS_PER_TICK/1000; // Seconds
	interval.it_value.tv_usec = (MS_PER_TICK * 1000) % 1000000; // Microseconds
	interval.it_interval = interval.it_value;

	if(setitimer(ITIMER_REAL, &interval, NULL) == -1)
	{
		p1perror(2, "Bad timer\n");
		for(int i = 0; i < num_proccs; i++)
		{
			kill(array[i].pid, SIGKILL);
		}
		goto cleanup;
	}
	alrm_handler(SIGALRM);

	while(active_processes)
	{
		pause();
	}

	cleanup:
		q->destroy(q);
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

	// Set quantum
	quantum = MS_PER_TICK * ((quantum+1) / MS_PER_TICK);
	// Isnt the previous line just funcionally equivalent quantum + 1?
	ticks_in_quantum = quantum / MS_PER_TICK;

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
