// University of Oregon CIS 314 Project 2, Part 1
// Authored by Cole Pendergraft

#include <stdio.h>

// I began this problem by working on paper, listing out all the masks I would need to
// preserve the n least significant bits for n = [1, 31] in the hopes that I found a pattern while
// looking at all the values at once. The issue is that there is a lot of patterns to
// look at with the table I constructed, so I spent a lot of time messing around with &, |, and 
// ~ operations before I started looking at the masks in their integer form rather than
// in hex, and that was when things began to fall into place and I realized I this whole
// problem boiled down to math and not logic operators.

unsigned int mask(int n){
	// I figued out I would have to do some sort of multiplying or dividing for this calculation, but
	// we aren't allowed to use most arithmetic operators for this assignment, so I knew I
	// would have to use bit shifting in some regard to either multiply or divide.  Since I was
	// going to be using bit shifting, I knew I had to think in terms of 2^n since bit shifting
	// left is equivalent to multiplying by 2^n and bit shifting right is equivalent to dividing by
	// 2^n.

	// This is where having a table of values was helpful, because I could look at all of my
	// expected outcomes at once and try to find some pattern in them that relates to 2^n.

	// I started at n = 1, for which we needed a mask of 0x1 = 1. Writing this in terms of 2^n,
	// I found that 0x1 = 1 = 2 - 1 = (2^1) - 1
	// After noticing this, I tried to write some more of my values in this format, 
	// If n = 2, we need a mask of 0x3 = 3 = 4 - 1 = (2^2) - 1
	// If n = 3, we need a mask of 0x7 = 7 = 8 - 1 = (2^3) - 1
	// If n = 4, we need a mask of 0xF = 15 = 16 - 1 = (2^4) - 1
	// If n = 5, we need a mask of 0x1F = 31 = 32 - 1 = (2^5) - 1
	// Hopefully the pattern has become apparent at this point. Knowing this pattern,
	// all I had to do was write the operation using allowed bitwise notation, where
	// (2^n) = (1 << n), and since we are allowed to use subtraction  I didn't
	// have to change anything to subtract by 1.

	unsigned int mask = (1 << n) - 1;
	return mask;
}

void main(){
	int i;
	for(i = 1; i < 32; i++){
		printf("For n = %i our mask is 0x%X\n", i, mask(i));
	}
}
