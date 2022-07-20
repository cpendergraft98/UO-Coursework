/* 
CIS 314 Project 4, Part 3
Author: Cole Pendergraft
*/

#include <stdio.h>
#include <stdlib.h>

/* 
Code compiled with gcc -Og -S for my own reference. 

fact:
.LFB22:
	cmpq $1, %rdi 		# if(x <= 1)

	jle .L3		# jump to L3 if x <= 1

	pushq %rbx	# pushes px onto stack when we initialize it.
							# We know %rbx stores px from the next line 

	movq %rdi, %rbx		# long px = x
										# %rdi stores x, so this is %rbx = x
										# Only time something is set to x is when long px = x
										# So %rbx must store px

	leaq -1(%rdi), %rdi

	call fact	# long fx = fact(x - 1)
					# recursive use of fact function

	imulq %rbx, %rax		# px * fx
											# %rbx stores px, %rax must store fx

	popq %rbx	# removes px from stack  because we are about to return so we no
							# longer need px or %rbx

	ret
.L3
	movl $1, %eax		# Executes if x <= 1
									# Set value in return registry = 1

	ret 		# Returns value stored in return register

*/

long fact(long x){
	if (x <= 1){
		return 1;
	}
	// I used the above assembly code to determine where in the function the 
	// pop and push methods are seen.

	long px = x;  
	long fx = fact(x - 1);	// Here is where px, stored in %rbx, is pushed on to the stack.
							// The main reason we push is that this particular function
							// has a funct call in it, and all functs use the same registers. Without a
							// stack, when we make the recursive call to fact within the function we
							// would overwrite %rbx with a new px, which will cause us to lose the
							// old value. By pushing %rbx onto the stack we stores its value in
							// a temporary location, which means in later calls we can
							// store different values in %rbx, but still pop the original value from
							// the stack which overwrites %rbx with whatever value is popped. In
							// this way, %rbx can be reused in subsequent calls without losing
							// the original or subsequent px values, as they are on the stack 
							// just waiting to be popped out and reassigned to %rbx. This is why
							// we don't have hundreds of registers, because each one can 
							// effectively store multiple values by using an associated stack
							// and access those values using pop. It's like putting those values
							// that aren't in use into a waiting room until we need them again.

	return px * fx;  // Here is where px, stored in %rbx, is popped from the stack
								// Anything that is pushed onto the stack must eventually be 
								// popped back out, because the stack is a temporary storage
								// location to save register values so that those same registers
								// can be used again in calls. When this return statement executes,
								// it is recognized as being the end of the code, so the compiler
								// knows that it should dump the value stored on the top of the stack
								// so that crashes don't occur. %rbx is then overwritten
								// with whatever value is at the top of the stack, and all other
								// elements move up in the stack. As the nested return statements
								// execute, values are popped from the stack until it is empty and 
								// %rbx once again stores the original value for px.
}


int main(){
	printf("=Test 1 executing=\n");
	printf("Test 1 out:%ld\n", fact(1));

	printf("=Test 2 executing=\n");
	printf("Test 2 out:%ld\n", fact(2));

	printf("=Test 3 executing=\n");
	printf("Test 3 out:%ld\n", fact(3));

	printf("=Test 4 executing=\n");
	printf("Test 4 out:%ld\n", fact(4));

	printf("=Test 5 executing=\n");
	printf("Test 5 out:%ld\n", fact(5));
	return 0;
}
