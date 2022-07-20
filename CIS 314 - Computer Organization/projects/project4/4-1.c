/*
CIS 314 Project 4, Part 1
Author: Cole Pendergraft
*/

#include <stdio.h>
#include <stdlib.h>

/*
x86-64 Code:

loop:		# Beginning of loop function, variable instantiation occurs.

	# First, we note that as per convention, %rdi stores long a and %rsi stores
	# long b.

	movq %rsi, %rcx	# Stores long b in %rcx without removing from %rsi
									# movq ----- %rsi, %rcx ----- %rcx = %rsi
									# %rcx is the counter register so long b  must be used to
									# increment the for loop.
									# Occurs without a dedicated line in the function so that value
									# of b isn't changed when incrementing.

	movl $1, %eax		# long mask = 1;
									# movl ----- $1, %eax ----- %eax = 1
									# Only instantiate 2 variables in loop, long result and long mask.
									# We know result = 0, so the only other variable this could
									# refer to is mask.
									#1 is an int, so it is stored in %eax, the int reg
									# for %rax.
									# Thus, mask is stored in %rax, with its integer value
									# 1 stored in %eax.

									# This is an aside, but it doesn't immediately make sense to
									# me why mask was stored in %rax when the long result = 0
									# line comes before it, it seems like the mask variable is is
									# instantiated before the result variable when I would have
									# expected the opposite.

	movl $0, %edx		# long result = 0;
									# movl ---- $0, %edx ---- %edx = 0
									# We are given that long result = 0.
									# 0 is an int, so it is stored in %edx, the int reg
									# for %rdx.
									# Thus, result is in %rdx, with its integer value 0 stored in
									# %edx.

.L2		# For loop start

	testq %rax, %rax	# mask != 0
									# testq sets the zero flag if
									# %rax & %rax == 0. %rax stores mask.
									# So, ZF is set if mask & mask == 0, meaning
									# mask == 0.  If the mask == 0, we want to
									# exit the loop, so we want to end the loop
									# if ZF is set after testq executes. Thus,
									# we use a jump instruction that executes
									# if ZF is set, which is je.

	je			.L4	# Jump to for loop end if zero flag is passed

	movq %rax, %r8	# Stores mask in %r8 without removing from %rax
									# movq ----- %rax, %r8 ----- %r8 = %rax
									# Occurs without a dedicated line  so the next line
									# can execute without  changing value in %rax.

	andq %rdi, %r8	# mask & a
									# andq ----- %rdi, %r8 ----- %r8 &= %rdi
									# From the previous line we know %r8 stores
									# mask.
									# Per convention, we know %rdi stores a.
									# %r8 now stores (mask & a).
									# Occurs without a dedicated line in order to condense
									# (mask & a) into a single register %r8 for the next line.

	orq     %r8, %rdx	# result |= (mask & a)
									# orq ----- %r8, %rdx ----- %rdx |= %r8
									# We know %rdx stores result
									# From the previous line, we know %r8 stores (mask & a)
									# %rdx now stores result | (mask & a)

	salq    %cl, %rax	# mask << = b
									# salq ------ %cl, %rax ----- %rax <<= %cl
									# We know %rax stores mask
									# %cl is the lower 8 bit register for %cx, %cx is the
									# 16 bit register for %ecx, %ecx is the 32 bit register for
									# %rcx, and at the very beginning we stored long b in %rcx,
									# so %cl stores the lower 8 bits of b.
									# Mask is being incremented for the next for loop execution

									# This is an aside, but I'm not entirely sure why b gets passed
									# as an 8 bit value when mask <<= b is executed, since b is stored
									# as a 32 bit long int in the 64 bit register %rcx. It seems
									# like the <<= automatically converts b to its lower 8 bits even
									# if the long value is passed in, and I'm not entirely
									# sure why that happens.

	jmp    .L2	# Jump to start of for loop where testq is performed again.

.L4		# For loop end

	movq %rdx, %rax	# stores result in %rax
										# movq ----- %rdx, %rax ----- %rax = %rdx
										# %rax is our return register, it is always returned
										# from the function. %rax currently stores mask, but we
										# want to return result, which is stored in %rdx. Thus, when
										# return result is called, %rax is set to %rdx, so now %rax stores
										# the result and not mask for the return. This occurs without a
										# dedicated line in the function to ensure %rax stores the value
										# we seek to return.

	return 	# return result
*/

// Code that generates above x86-64 code:

long loop(long a, long b){
	long result = 0;
	for(long mask = 1; mask != 0; mask <<= b){
		result |= (mask & a);
	}
	return result;
}

// Main to test our loop function:
int main(){
	printf("Executing test1.\n");
	printf("Test1 output: %ld\n", loop(1, 5));

	printf("Executing test2.\n");
	printf("Test2 output: %ld\n", loop(2, 4));

	printf("Executing test3. \n");
	printf("Test3 output: %ld\n", loop(3, 3));

	printf("Executing test4. \n");
	printf("Test1 output: %ld\n", loop(4, 2));

	printf("Executing test5. \n");
	printf("Test5 output: %ld\n", loop(5, 1));

	return 0;
}
