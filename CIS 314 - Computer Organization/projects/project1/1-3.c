// University of Oregon CIS 314 Project 1, Part 3
// Authored by Cole Pendergraft
// Last modified on 01/14/2021

#include <stdio.h>

int oddBit(unsigned long int x){
	// I had to change this to an unsigned long int because I was getting errors when I tried to pass in something
	// like 0xFFFFFFFF, it was attempting to cast the unsigned long int 0xFFFFFFFF to an unsigned int.
	//
	// Okay, this part requires a lot of explanation before I get into it because I spent a lot of time working out
	// this problem on paper before I even approached it in code, and I wanted to explain my math before getting
	// into the bulk of the code.
	//
	// I figured out early on that in order to isolate the odd bits, I would need to use a mask composed entirely of 
	// hex values that only have 1's in odd positions. To do this, I used 0xAAAAAAAA, as A in binary is 1010, so it has 
	// 1's in every odd position. After this, I moved on to doing some math. I took the digits 0-9 and converted them to
	// binary, and then checked what my output was when I use the and operator on those binary values with 1010. 
	// I discovered that every binary value that had no 1's in odd positions would become 0, and that those that
	// did have at least a single 1 in an odd bit position would be some value other than 0. It may not be the same
	// as the starting value, but it was definitely not zero. For example:
	//
	// The value 1 in binary is 0001, we see that it has no 1's in odd positions. If we do 1010 & 0001, we get 0000 = 0.
	//
	// The value 2 in binary is 0010, we see that it does have a 1 in an odd position. If we do 1010 & 0010, we get 
	// 0010 = 2.
	//
	// The value 4 in binary is 0100, we see that it has no 1's in odd positions. If we do 1010 & 0100, we get 0000 = 0.
	//
	// The value 6 in binary is 0110, we see that it does have 1's in odd positions. If we do 1010 & 0110, we get
	// 0010 = 2 which is not 6, but that is okay because it is also not zero.
	//
	// I performed this calculation for the digits 0-9, and found this trend consistent across all digits. With this in mind,
	// I think it is reasonable to assume this trend will remain true for hex values A, B, C, D, E, and F, where any that 
	// have no ones in odd positions will become 0 when used with the and operator on A.
	//
	// What all this means is that after we use the and operator on our mask and input value, all we need to do is
	// check if the output value is equal to 0x00000000. If it is, then that means none of the values that compose
	// our input value have 1's in odd positions, and the program will return 0.

	// Instantiate variables:
	unsigned int mask;
	unsigned int check;

	mask = 0xAAAAAAAA;
	// I explained why I am using this mask above

	check = x & mask;
	// Again, this is explained above. If our check value = 0x00000000, then the program should return 0, otherwise
	// it should return 1.

	return !(!check);
	// Our book tells us that logical operations in C recognize non-zero values as true, and values of 0 as false. However, we only have one value 
	// we need to check, and all the logical operators except ! requre two values to compare. This means that we have to use ! in order to return 
	// true or false, as we are not allowed to use != by the project specs. We want to return false if check = 0x00000000, but the not operator
	// will return true if check = 0x00000000 and we do !check, because check is all zeros. In order to correct this, we do !(!check), as in that case,
	// if check = 0x00000000, then we have !(true), and if check is nonzero we have !(false)
}

void main(){
	printf("Test 1:\n Input: 0x1\n Expected output: 0\n Actual output: %i\n", oddBit(0x1), "\n");
	printf("Test 2:\n Input: 0x2\n Expected output: 1\n Actual output: %i\n", oddBit(0x2), "\n");
	printf("Test 3:\n Input: 0x3\n Expected output: 1\n Actual output: %i\n", oddBit(0x3), "\n");
	printf("Test 4:\n Input: 0x4\n Expected output: 0\n Actual output: %i\n", oddBit(0x4), "\n");
	printf("Test 5:\n Input: 0xFFFFFFFF\n Expected output: 1\n Actual output: %i\n", oddBit(0xFFFFFFFFF), "\n");
	printf("Test 6:\n Input: 0xAAAAAAAA\n Expected output: 1\n Actual output: %i\n", oddBit(0xAAAAAAAA), "\n");
	printf("Test 7:\n Input: 0x55555555\n Expected output: 0\n Actual output: %i\n", oddBit(0x55555555), "\n");
}
