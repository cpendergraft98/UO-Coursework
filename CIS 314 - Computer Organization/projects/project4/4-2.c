/*
CIS 314 Project 4, Part 2
Author: Cole Pendergraft
*/

#include <stdio.h>
#include <stdlib.h>

/*
// Given C code

int sum(int from, int to){
	int result = 0;
	do{
		result += from;
		++from;
	} while (from <= to);
	return result;
}
*/

/*
//Part a) Convert code to goto version:

int sum(int from, int to){
	int result = 0;  // Variable initialization

	goto start;  // Do while loops run once no matter what, so we need to ensure
						// the loop body executes one time regardless of the check. This means
					   // we need a label associated with loop body that we can goto to execute
					   // before any checking is done.

	check:  // Goto label that contains the check for from <= to

		if(from > to){  // We want from <= to, so here we check
								 // if our from <= to condition has been broken by checking
								// if from > to.

			goto f_g_t;  // If the condition is broken, we want to return our result,
								// So jump to label containing return.
		}

		start:  // Start label contains loop body so we can ensure that the loop executes 
					// at least one time. This label is only used once at the start. Is
					// part of the check label.

			result += from;  // Sets new result = result + from

			++from;  // Increments from

			goto check;  // Loop will definitely execute once, now we should start checking
									// to ensure from <= to for the remainder of iterations. Since the 
									// loop body is also within the check label, this loop body will 
									// execute again if the check passes, and the goto check again,
									// making it function like a do while loop

	f_g_t:  // Label associated with from being greater than to

		return result;  // If from > to, we exit loop and return result
}
*/

// Part b) Implement code in x86-64

/*
For my own reference I have included int x86-64 code for the sum function

%rdi stores long from
%rsi stores long to
%rax stores result

sum:
	.LFB22:
		movl $0, %eax	# sets val of result to 0 (long result = 0)

	.L2
		addl %edi, %eax	# sets val of result = result + from (result += from)
		addl $1, %edi	# sets val of from = from + 1 (++from)
		cmpl %esi, %edi	# checks if from <= to
		jle .L2 	# jumps to start of loop if from <= to
		ret
*/


long sum(long from, long to){
	// Declare and initialize result var - *do not modify*.
	long result = 0;

	// Ensure that argument *from* is in %rdi,
	// argument *to* is in %rsi, *result* is in %rax - *do not
	// modify*
	__asm__("movq %0, %%rdi # from in rdi;" : : "r" ( from ));
	__asm__("movq %0, %%rsi # to in rsi;" : : "r" ( to ));
	__asm__("movq %0, %%rax # result in rax;" : : "r" ( result ));

	// Your x86-64 code goes below - comment each instruction...
	__asm__(
		// TODO - Replace the two lines below with add, compare,
		// jump instructions, labels, etc as necessary to implement 
		// the loop
		// %eax already = 0 after long result = 0 executes.

		// Compiled assembly code above can essentially just be copied.
		// \n included to improve readability when compiled with gcc -Og -S

		".L2:\n"		// Label related to our while loop

		"addl %edi, %eax;\n"		// result += from
													// addl %edi, %eax --- %eax = %eax + %edi
													// %edi stores int value of %rdi. %rdi holds *from*
													// %eax stores int value of %rax. %rax holds *result*
													// Int value of result becomes %edi + %eax		

		"addl $1, %edi;\n"			// ++from
													// addl $1, %edi --- %edi = %edi + 1
													// %edi  stores int value of *from*.
													// After executing, *from* has been incremented by 1
													// and %edi = *from* + 1

		"cmpl %esi, %edi;\n"		// while(from <= to)
													// Checking if our while loop should continue
													// executing or exit.
													// cmpl sets ZF if a == b
													// sets SF  if a-b < 0, which is equiv to a < b .
													// So, if *from* == *to*, we set ZF which causes
													// the follwing jump instruction to execute and
													// restarts the loop.
													// If *from* < *to*, we set SF which causes the 
													// following jump instruction to execute and
													// restarts the loop.

		"jle .L2;\n"		// Restarts loop if conditions from cmpl are met
								// The jle jump instruction executes if the previous line sets
								// (SF^OF)|ZF.
								// That is, it executes if 
								// SF is set and OF is not set, OR  ZF is set
								// OF is set and SF is not set, OR ZF is set
								// From previous line:
								// If *from* = *to*, ZF set, restarting loop
								// If *from* - *to* < 0 (*from* < *to*) SF set, restarting loop
								// Otherwise, instruction ignored and the next line
								// executes, exiting loop.
		);

	// Ensure that *result* is in %rax for return - *do not modify*.
	__asm__("movq %%rax, %0  # result in rax;" : "=r" ( result ));
	return result;
}

int main(){
	printf("==Executing test 1==\n");
	printf("Test 1 output: %ld\n", sum(1, 6));
	printf("==========================\n");

	printf("==Executing test 2==\n");
    printf("Test 2 output: %ld\n", sum(3, 5));
	printf("==========================\n");

	printf("==Executing test 3==\n");
	printf("Test 3 output: %ld\n", sum(5, 3));
	printf("==========================\n");
	return 0;
}
