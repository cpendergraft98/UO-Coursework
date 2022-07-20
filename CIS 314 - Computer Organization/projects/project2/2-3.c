// University of Oregon CIS 314 Project 2, Part 3
// Authored by Cole Pendergraft

#include <stdio.h>

// Big block of text here, but this is all there is for this part. I wrote a truth table to solve this and
// I wanted to include it because it demonstrates my thought process well.
// Since sy and sx are the isolated sign bits, if sy = 0 then y is positive, and if sy = 1 then y 
// negative. The same is true for x.

// ux <= uy | sy = 0 | sx = 0 | our return should be
//        1                1            1                     1
//        1                1            0                     1
//        1                0            0                     0
//        1                0            1                     0
//        0                1            1                     0
//        0                1            0                     1
//        0                0            0                     1
//        0                0            1                     0

// From this chart we can determine the situations in which we want our function to be true
// and we want it to be false, and there are two outcomes to consider, one where 
// ux <= uy, and one where ux >= uy.
// We can see that if ux <= uy and sy = 0 (so y is positive), then we want our function to spit
// out 1
// Alternatively, we see that if ux >= uy and sx != 0 (so x is negative), then we want our 
// function to also spit out 1. 
// However, if neither of those two above conditions are met, (i.e.  ux <= uy and sy = 1 or 
// ux >= uy and sx = 0) then the function will return 0.
// What is written from lines 22-25 is essentially the psuedocode for this problem.
// If (ux <= uy AND sy = 0 is true) OR  (ux >= uy AND sx = 1 is true) then we want to return true.
// If both of those statements are false then that means our function should return false.

int le(float x, float y){
	unsigned int ux = *((unsigned int*) &x); // convert x raw bits
	unsigned int uy = *((unsigned int*) &y); // convert y raw bits
	unsigned int sx = ux >> 31; // extract sign bit of ux
	unsigned int sy = uy >> 31; // extract sign bit of uy
	ux <<= 1; //drop sign bit of ux
	uy <<= 1; //drop sign bit of uy
	return ((sy == 0) && (ux <= uy)) || ((sx == 1) && (ux >= uy));
}

void main(){
	printf("%i\n", le(0.0f, 0.0f));
	printf("%i\n", le(-0.0f, 0.0f));
	printf("%i\n", le(-1.0f, -1.0f));
	printf("%i\n", le(1.0f, 1.0f));
	printf("%i\n", le(-1.0f, 0.0f));
	printf("%i\n", le(0.0f, 1.0f));
	printf("%i\n", le(1.0f, 0.0f));
	printf("%i\n", le(0.0f, -1.0f));
	printf("%i\n", le(-1.0f, -2.0f));
}