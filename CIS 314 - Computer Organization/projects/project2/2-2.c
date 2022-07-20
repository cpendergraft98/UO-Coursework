// University of Oregon CIS 314 Project 2, Part 2
// Authored by Cole Pendergraft

#include <stdio.h>

unsigned int extract(unsigned int x, int i){
	// I first approached this problem using a mask of 0xFF that I shifted around to isolate the 
	// bit I am interested in and convert the rest to 0, but I quickly realized that wouldn't work
	// because it would leave me with something like 0x00XX0000, and when I tried to convert
	// to a signed int it wouldn't work because the left most bit is equal to zero, so the right
	// shift would just leave it at zero instead of filling it with the proper sign bits. This told
	// me that a mask is not the way to go here, and I would instead have to use shifting.

	// I am also pretty sure that all my variables here need to be ints, if I have them as
	// usigned ints then no matter what I do I won't be able to sign extend them, because
	// the arithmetic right shift operator only adds 0s to the left side if the value is 
	// unsigned and not signed. I would just be casting a signed int to an unsigned int.

	int shift = ((3 -i) << 3); 
	int no_sign = x << shift;
	// This was my solution to the issue I discussed above. Instead of using a bitmask, I shift
	// the value x so that the byte I want to preserve is at the very front. So if we have
	// 0xABCDEF00 and we wanted to isolate byte i = 1 ( EF ), we would need to left shift by
	// 16 in order to have that particular byte at the front. My shift function ensures that the 
	// byte we want to preserve is shifted up to the front based on its position i. So, we have 
	// shift = (3 - 1) << 3 = 2 * 2^3 = 16. When we apply that shift we will then have 
	// 0xEF000000 and we can then right shift the whole thing so that EF becomes the
	// 0th byte, and that will also sign extend the value.

	int add_sign = no_sign >> 24;
	// We know that if the value we are using the arithmetic right shift on is signed then the
	// following is true:
	// If the left most bit is 0, then the remaining left bit positions will be filled with 0
	// If the left most bit is 1, then the remaining left bit positions will be filled with 1
	// So we can use the right shift to sign extend our values.
	// We shift by 24 here because now we want the preserved byte to go all the way from
	// position 3 to position 0 (as per project specs), which amounts to 24 bytes shifted.
	// Using our previous example of 0xEF000000, after this line executes we will have
	// 0xFFFFFFEF.
	return add_sign;
}

void main(){
	printf("0x%X\n", extract(0xABCDEF00, 0));
	printf("0x%X\n", extract(0xABCDEF00, 1));
	printf("0x%X\n", extract(0xABCDEF00, 2));
	printf("0x%X\n", extract(0xABCDEF00, 3));
	printf("0x%X\n", extract(0x12345678, 1));
	printf("0x%X\n", extract(0x12345678, 2));
	printf("0x%X\n", extract(0x12345678, 3));
	printf("0x%X\n", extract(0x12345678, 4));
}