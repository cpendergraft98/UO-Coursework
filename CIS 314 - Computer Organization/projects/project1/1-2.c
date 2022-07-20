// University of Oregon CIS 314 Project 1, Part 2
// Authored by Cole Pendergraft
// Last modified on 01/14/2021

#include <stdio.h>

unsigned int replace(unsigned int x, int i, unsigned char b){
	// So for this part, we want to remove the byte at position i of our 32 bit word, and replace it with b

	// First we initialize our variables
	unsigned int startmask;
	unsigned int startmask_flip;
	unsigned int adjusted_x;
	unsigned int rep_byte;
	unsigned int final;

	startmask = 0xFF;
	// Since we are only going to be replacing exactly one byte out of our input value, our starting mask needs to
	// be just on byte in size. We want to start with 0xFF and not 0x00 because the bitwise shift operator fills new
	// space with 0's, so if we start with 0x00 the best we can hope for is just adding more 0's to that mask. Our best
	// option, then, is to create a mask that would typically preserve only a single byte, and then invert it so that it
	// preserves every byte aside from that one.

	startmask = startmask << (i << 3);
	// Here we shift our bitmask according to what specific byte we are seeking to replace. since each byte is made
	// up by two bits, and each bit is 4 digits long, 1 byte is effictively 8 digits long, which means we need to
	// shift by a multiple of 8 to access the specific byte we are looking for. This means that we want to have i*8, but
	// we can't use arithmetic operators in this project. The equivalent to multiplying by 8 is shifting left 3, as we have
	// learned that i << x = i * 2^x. We also need to remember that this mask will be inverted later on down the line.
	//
	// Shifting logic:
	//We effectively start with a mask of 0x000000FF, so :
	// If we want to replace the 0th byte we need to shift by 0 * 8 = 0, so our mask is still 0x000000FF. 
	// If we want to replace the 1st byte, we shift by 1 * 8 = 8, so our mask becomes 0x0000FF00. 
	// If we want to replace the 2nd byte, we shift by 2 * 8 = 16, so our mask becomes 0x00FF0000.
	// If we want to replace the 3rd byte, we shift by 3 * 8 = 24, so our mask becomes 0xFF000000.

	startmask_flip = ~startmask;
	// As it stands, our mask is such that it will actually preserve the bit that we are trying to replace, rather
	// than remove it.
	// I.e. We have x = 0x12345678 and we want to replace the 2nd byte, so our mask is 0x00FF0000
	//   0x12345678
	//&  0x00FF0000
	//--------------------
	//   0x00340000
	// We are now preserving the byte we want to replace.
	// So what we want to do instead is invert our mask so that we preserve every byte other than the one we want
	// replace. By doing this, the above example becomes:
	// x = 0x12345678 and our mask = 0xFF00FFFF
	//   0x12345678
	//& 0xFF00FFFF
	//-------------------
	//   0x12005678
	// Now we have opened up a space to input the new byte using the or method.

	adjusted_x = x & startmask_flip;
	// This here is the code that combines our x input with our inverted mask in order to remove
	// the byte that is going to be replaced. See above comments for examples of how the 
	// & operator works with our x and inverted mask.

	rep_byte = b << (i << 3);
	// Now we have to adjust our input byte so that it is in the postion we want it to be in when we use the
	// or operator. This line functions in exactly the same way as line 24.
	// I.e. assume b = 0xAB
	// We are essentially starting with 0x000000AB.
	// If we want to insert at position 0, we shift by 0, making our b = 0x000000AB
	// If we want to insert at position 1, we shift by 8, making our b = 0x0000AB00
	// If we want to insert at position 2, we shift by 16, making our b = 0x00AB0000
	// If we want to insert at position 3, we shift by 24, making our b = 0xAB000000

	final = adjusted_x | rep_byte;
	// Now all we have to do is replace our bytes using an or statment, this way all that are not 0 | 0 are kept.
	// I.e. suppose we have x = 0x12345678 and we are inserting 0xAB at position 2, and that the rest of the code up to 
	// this point has executed.
	// Then in this case we have adjusted x = 0x12005678 | rep_byte = 0x00AB0000
	//   0x12005678
	// | 0x00AB0000
	//-----------------------
	// 0x12AB5678

	// Print statements for debugging
	//printf("Initial input: 0x%X\n", x);
	//printf("Starting mask: 0x%X\n", startmask);
	//printf("Mask after inversion: 0x%X\n", startmask_flip);
	//printf("Adjusted x value after combination with startmask_flip: 0x%X\n", adjusted_x);
	//printf("Byte to be inserted into adjusted_x: 0x%X\n", rep_byte);
	//printf("Final value to be returned: 0x%X\n", final);

	printf("Combination function returns: 0x%X\n", final);
	// Once again, this line is just here to show the hex representation of our final value. I can't seem to store
	// the hex value in a variable and then return it at the end still as a hex value, C just returns the integer 
	// representation of that hex value instead, so I'm using a print satatment and just letting the function 
	// return the integer value.

	return final;
}

void main(){
	printf("Testing replace function \n");
	printf("\n");

	printf("Test 1:\n x = 0x12345678 \n i = 3 \n b = 0xAB \n Expected outcome: 0xAB345678\n");
	replace(0x12345678, 3, 0xAB);
	printf("\n");

	printf("Test 2:\n x = 0x12345678 \n i = 2 \n b = 0xAB \n Expected outcome: 0x12AB5678\n");
	replace(0x12345678, 2, 0xAB);
	printf("\n");

	printf("Test 3:\n x = 0x12345678 \n i = 1 \n b = 0xAB \n Expected outcome: 0x1234AB78\n");
	replace(0x12345678, 1, 0xAB);
	printf("\n");

	printf("Test 4:\n x = 0x12345678 \n i = 0 \n b = 0xAB \n Expected outcome: 0x123456AB\n");
	replace(0x12345678, 0, 0xAB);
	printf("\n");

	printf("Test 5:\n x = 0x12345678 \n i = 2 \n b = 0x47 \n Expected outcome: 0x12475678\n");
	replace(0x12345678, 2, 0x47);
	printf("\n");

	printf("Test 6:\n x = 0x12345678 \n i = 1 \n b = 0x95 \n Expected outcome: 0x12349578\n");
	replace(0x12345678, 1, 0x95);
	printf("\n");
}
