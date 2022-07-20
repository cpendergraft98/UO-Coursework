/*
CIS 314 Project 7, Part 1

Author: Cole Pendergraft
*/
#include <stdio.h>
#include <stdlib.h>

unsigned int getOffset(unsigned int address){
  unsigned int mask = 0x000000FF; // Create a mask to isolate first 8 bits
  unsigned int new = address & mask;  // Combine mask and address
  return new; //Bits are already at the start of new, no shifting needed.
}

unsigned int getSet(unsigned int address){
  unsigned int mask = 0x00000F00; // Create a mask to isolate bits 9-12
  unsigned int new = address & mask; // Combine mask and address
  new = new >> 8; // Need to right shift 8 bits so our focal bits are at the start
  return new; // Return set
}

unsigned int getTag(unsigned int address){
  unsigned int mask = 0xFFFFF000; // Create a mask to isolate bits 13-32
  unsigned int new = address & mask; // Combine mask and address
  new = new >> 12; // Need to right shift 12 bits so our focal bits are at the start
  return new;  // Return tag
}


int main(){

printf("\n");
unsigned int off = getOffset(0x02);
printf("offset: %X\n", off);

printf("\n");
unsigned int set = getSet(0x02);
printf("set: %X\n", set);

printf("\n");
unsigned int tag = getTag(0x02);
printf("tag: %X\n", tag);

return 0;
}
