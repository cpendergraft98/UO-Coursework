// CIS 314 Project 3, Part 2
// Author: Cole Pendergraft

#include <stdio.h>
#include <stdlib.h>

/* 
Whole bunch of translation here from the machine code to the variables we are
using, the actual function is way down there.

From the powerpoint from monday 01/25 I got the follwing information:

addq ----- Src,Dest ----- Dest = Dest + Src
imulq ----- Src, Dest ----- Dest = Dest * Src
salq ----- Src, Dest ----- Dest = Dest << Src
sarq ----- Src, Dest ----- Dest = Dest >> Src
movq ----- Src, Dest ----- Dest = Src
xorq ----- Src, Dest ----- Dest = Dest ^ Src 

Translated into our machine code:

addq ----- %rsi, %rdx ----- %rdx = %rdx + %rsi
imulq ----- %rdx, %rdi ----- %rdi = %rdi * %rdx
salq ----- $63, %rdx ----- %rdx = %rdx << 63
sarq ----- $63, %rdx ----- %rdx = %rdx >> 63
movq ----- %rdi, %rax ----- %rax = %rdi
xorq ----- %rdx, %rax ----- %rax = %rax ^ %rdx

Where $63 is equivalent to 63 literal 

We have that x is in %rdi, y is in %rsi, z is in %rdx, and %rax is used to hold our return.
Translating that into our above machine code we get:

addq ----- y, z ----- z = z + y
imulq ----- z, x ----- x = x * z
salq ----- 63, z ----- z = z << 63
sarq ----- 63, z ----- z = z >> 63
movq ----- x, ret ----- ret = x
xorq ----- z, ret----- ret = ret ^ z

And there we have our machine code fullly translated! Now all we need to do is write the
f function that executes those operations in that order and returns the value.
*/

long f(long x, long y, long z){
	// Our eventual return value
	long ret;

	// addq
	z = z + y;

	// imulq
	x = x * z;

	// salq
	z = z << 63;

	// sarq
	z = z >> 63;

	// movq
	ret = x;

	// xorq
	ret = ret^z;

	return ret;
}

int main(){
	printf("Testing f(1, 2, 4): %ld\n", f(1, 2, 4) );
	printf("Testing f(3, 5, 7): %ld\n", f(3, 5, 7));
	printf("Testing f(10, 20, 30): %ld\n", f(10, 20 ,30));

	return 0;
}