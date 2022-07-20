// University of Oregon CIS 314 Project 1, Part 3
// Authored by Cole Pendergraft
// Last modified on 01/14/2021

#include <stdio.h>

void printBytes(unsigned char *start, int len){
	for (int i = 0; i < len; i++){
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void printInt(int x){
	printBytes((unsigned char *) &x, sizeof(int));
}

void printFloat(float x){
	printBytes((unsigned char *) &x, sizeof(float));
}

void printShort(short x){
	printBytes((unsigned char *) &x, sizeof(short));
}

void printLong(long x){
	printBytes((unsigned char *) &x, sizeof(long));
}

void printLongLong(long long x){
	printBytes((unsigned char *) &x, sizeof(long long));
}

void printDouble(double x){
	printBytes((unsigned char *) &x, sizeof(double));
}

void main(){
	// I used the same value in all of the functions because it helped me to compare one output to the next and actually understand what the code is doing.
	printf("Testing printInt\n");
	printInt(32);
	// First thing I notice: this data type has 4 bytes which equates to 32 bit, so it is a 32 bit integer.
	// I also believe this ordering to match the big endian ordering that our book talks about.

	printf("Testing printFloat\n");
	printFloat(32);
	// First thing I notice: this data type prints in reverse! Whereas the int data type displayed
	// bytes in position 3, then 2, then 1, and finally 0 in that order, this float data type outputs bytes
	// 0, 1, 2, and 3 in that order. I think this would be equivalent to little endian as it was discussed in our
	// textbook, and I find that relatively interesting. The book describes that little endian isn't necessarily
	// better than big endian and vice versa, so as long as one is chosen and adhered to then it is okay,
	// but it doesn't look like C adheres to one convention, it does little endian for floats and doubles, and
	// big endian for the rest. Since big endian  and little endian are effectively the same in terms of storage,
	// I wonder why C was built to be variable in that way. My guess is that when talking about floats,
	// the most significant bit is considered to be the last one, not the first.
	// I also note that this is a 32 bit value just like the previous part.

	printf("Testing printShort\n");
	printShort(32);
	// First thing I notice: this particular data  only has 16 bits of information.
	// This is another data type represented by big endian, so more inconsitency with the ordering structure. My
	// assumption here is that with integer based data types the most significant byte is the leading byte, so that
	// one at the front to be easily accessed.

	printf("Testing printLong\n");
	printLong(32);
	// First thing i notice: this particular data type has 64 bits of information.
	// Again we have a data type represented using big endian ordering. Looks like only decimal values
	// end up being represented as little endian, like I said before I think this is because the most significant
	// byte in an integer is the first one.

	printf("Testing printLongLong\n");
	printLongLong(32);
	// First thing I notice: this particular data type has 64 bits of information.
	// Unsurprisingly, since this data type is related to ints, it is also represented using big endian ordering.

	printf("Testing printDouble\n");
	printDouble(32);
	// First thing I notice: like the float, this data type outputs it's information opposite the order we would 
	// expect.
	// And now we are back to floating point representations, and the little endian ordering makes an
	// appearance again. I have already explained why I think this occurs, but that is only an assumption
	// and I am still really curious what the actual reason for representing floats using little endian ordeering is.
}
