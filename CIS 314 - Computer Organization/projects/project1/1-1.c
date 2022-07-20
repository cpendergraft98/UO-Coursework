// University of Oregon CIS 314 Project 1, Part 1
// Authored by Cole Pendergraft
// Last modified on 01/14/2021
//
// Hopefully my comments aren't too long, I definitely have a habit of over explaining my code. I tend to use my old homework
// assignments as my notes on future projects so it helps to have super detailed markdown. I will cut down on the comments in the future if this is too much.
// All four of the submissions look are commented like this, a thousand apologies to the TA that grades this.

#include <stdio.h>


unsigned int combine(unsigned int x, unsigned int  y){

	// Declaring Variables to be used
	unsigned int value;
	unsigned int xmask;
	unsigned int ymask;
	unsigned int endbytes;
	unsigned int startbytes;


	// This project spec is very well defined, as we want to do the exact same thing every time the program is run, 
	// preserve the first 3 bytes of the x value, and the last byte of the y value. This means our masks don't need to be 
	// variable and can instead be hardcoded into our program.

	// First, lets code the logic that will preserve bits 3 through 1 of our x value:

	xmask = 0xFFFFFF00;
	// If we & this hex value with our input hex value, then bytes 3 to 1 will be preserved, and the last byte will be 
	// converted to 0's that we can use | to get rid of later. The reason why this works is explained in late comments.

	startbytes = x & xmask;
	// Since we are using the and operator here, the program looks at our passed values in the following way:
	// Suppose our input is x = 0x12345678 .
	// If we have
	//
	//    0x12345678
	//& 0xFFFFFF00
	//-----------------------
	//    0x12345600
	//
	// Because our program will preserve any instance where there is no &0, as we know from the following truth table:
	// A B	&
	// 0 0	0
	// 0 1	0
	// 1 0	0
	// 1 1	1
	//
	// So when we have F & 4, the return is 4, but if we have 7 & 0, the return is 0.
	//
	// This also preserves any position where we have a zero before the last byte, which is nice as I thought that
	// would be a bug in my code. If we have something like 0 & F then it returns 0, which is what we want.
	//
	// After this part of the code executes, bytes 3 through 1 have been established, so now we just need to tackle 
	// the last two bits and then combine our values.

	// Now we can work on the logic that generates our final byte:

	ymask = 0x000000FF;
	// This mask operates in exactly the same way as the first, just that it preserves different values. Our x mask 
	// preserved bytest 3 through 1 of our x input, and this code will preserve byte 0 of our y input.

	endbytes = y & ymask;
	// Like before, I'm going to use an example to sort this out and demostrate what is going on.
	// Suppose our input is y = 0xABCDEF12, then this line of code equates to:
	//
	//   0xABCDEF12
	//& 0x000000FF
	//---------------------
	//    0x00000012
	//
	// Like before, where we have A & 0 we get false (based on our truth table) so the return is zero. If we have
	// 1 & F, we get true (also based on the truth table) so the return is 1 (what ever other value is being 
	// &'ed with F).

	// Now that we have our starting bytes and our ending bytes, all that is left is to combine them.

	value = startbytes | endbytes;
	// We definitely do not want to use the & operator here, as if we did it would look like this:
	// Suppose startbytes = 0x12345600 and endbytes = 0x00000012
	//
	//  0x012345600
	//& 0x00000012
	//---------------------
	//
	// Hopefully the reason why this won't work is apparent even without me actively solving the probelm. In every 
	// position we have something & 0, and that will always return 0, so if we & these two values we return just
	// 0x00000000
	// But, if we take a look at our | truth table:
	//
	// A B  |
	// 0 0  0
	// 0 1  1
	// 1 0  1
	// 1 1  1
	//
	// We see that if we or these two values, then it will preserve any postion where there is a nonzero component.
	// Nicely, it also preservers the value of 0 if we have something like 0 | 0, and doesn't change it to a 1.

	printf("The combined unsigned ints in hex is: 0x%X\n", value);
	// This line is just here to show the hex representation of our final value. I can't seem to store
	// the hex value in a variable and then return it at the end still as a hex value, C just returns the integer 
	// representation of that hex value instead, so I'm using a print satatment and just letting the function 
	// return the integer value.

	return value;
	// Returns the integer equivalent of the combined 32-bit words
}

void main(){
	printf("Testing Combine function\n");
	printf("\n");

	printf("Test 1: \n x = 0x12345678 \n y = 0xABCDEF00 \n Expected hex output: 0x12345600 \n");
	combine(0x12345678, 0xAB0DEF00);
	printf("\n");

	printf("Test 2: \n x = 0x50604355 \n y = 0x43967843 \n Expected hex output: 0x50604343 \n");
	combine(0x50604355, 0x43967843);
	printf("\n");

	printf("Test 3: \n x = 0x12345678 \n y = 0x00000000 \n Expected hex output: 0x12345600 \n");
	combine(0x12345678, 0x00000000);
	printf("\n");

	printf("Test 4: \n x = 0x00000000 \n y = 0xABCDEF00 \n Expected hex output: 0x0 \n");
	// Note that 0x00000000 = 0x0
	combine(0x00000000, 0xABCDEF00);
	printf("\n");

	printf("Test 5: \n x = 0x00000000 \n y = 0xABCDEF12 \n Expected hex output: 0x12 \n");
	// Note that 0x00000012 = 0x12
	combine(0x00000000, 0xABCDEF12);
	printf("\n");

	printf("Test 6: \n x = 0xABCDEF00 \n y = 0x12345678\n Expected hex output: 0xABCDEF78 \n");
	combine(0xABCDEF00, 0x12345678);
	printf("\n");
}
