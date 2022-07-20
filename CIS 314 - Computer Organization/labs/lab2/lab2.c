// Authored by Cole Pendergraft
// A B	&
// 0 0	0
// 0 1	0
// 1 0	0
// 1 1	1

// 00010111 & 00111011

// 		00010111
// &  00111011
// -------------------
// 		00010011

//More practice:
// A B 	|
// 0 0 	0
// 0 1 	1
// 1 0 	1
// 1 1 	1

// A B 	^
// 0 0 	0
// 0 1 	1
// 1 0 	1
// 1 1 	0

// 00010111 ^ 00111011
// 		00010111
// ^ 	00111011
// --------------------
// 		00101100

// 00010111 | 00111011
// 		00010111
// | 	00111011
// --------------------
// 		00111111

// ~00010111 => 11101000 (flips bits)

#include <stdio.h>
int isNegativeOrZero(int x){
	int neg = x & 0x80000000; //Seven zeros makes this a 32 bit value. 0x8 is a mask that preserves 
	// the first bit. Essentially says "only look at the first bit". 0x8 = 0b1000 (hex), 8 = 1000 (binary)
	// alternative: 
	// int neg = x >> 31; (shift right 31 times because 32 bit integer)
	int zero = !x; //flips 1's in binary to 0, and 0's to 1's
	return neg || zero;
}

int isPositiveOrZero(int x){
	return !(x >> 31);
}

void main() {
	printf("Test isNegativeOrZero for -45: %i\n", isNegativeOrZero(-45));
	printf("Test isNegativeOrZero for 0: %i\n", isNegativeOrZero(0));
	printf("Test isNegativeOrZero for 14: %i\n", isNegativeOrZero(14));
	printf("Test isPositiveOrZero for -45: %i\n", isPositiveOrZero(-45));
	printf("Test isPositiveOrZero for 0: %i\n", isPositiveOrZero(0));
	printf("Test isPositiveOrZero for 14: %i\n", isPositiveOrZero(14));
}