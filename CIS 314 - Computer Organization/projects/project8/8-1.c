/*
CIS 314 Project 8

Author: Cole Pendergraft
Helped by Colton Lobdell
*/

#include <stdio.h>
#include <stdlib.h>

struct Line{
  unsigned char data[4];
  unsigned int tag;
  unsigned char valid;
};

struct Cache{
  struct Line *lines;
  int numLines;
};

unsigned int getOffset(unsigned int address){
  // 4B blocks, so offset it bits 0-1
  return address & 0x3;
}

unsigned int getSet(unsigned int address){
  // 16 sets, so offset is bits 2-6
  return (address >> 2) & 0xF;
}

unsigned int getTag(unsigned int address){
  // Offset and set are 6 bits total, so tag is high-order 26 bits
  return address >> 6;
}

struct Cache* mallocCache(int numLines){
  // Malloc struct Cache pointer
  struct Cache *cache = malloc(16 * sizeof(struct Cache));

  // Set array size to numLines
  cache->numLines = numLines;

  // Malloc a pointer to an array of struct Line instances with length numLines
  cache->lines = (struct Line*)malloc(sizeof(struct Line) * numLines);

  // Set all of the valid elements of the line instances to 0
  for(int i = 0; i < numLines; i++){
    cache->lines[i].valid = 0;
  }
  // Return pointer to the struct Cache
  return cache;
}

void freeCache(struct Cache *cache){
  free(cache->lines);
  free(cache);
}

void printCache(struct Cache *cache){
  //Iterate through the whole cache
  for(int i = 0; i < cache->numLines; i++){
    // Check which lines have valid = 1
    if(cache->lines[i].valid){
      // Create a struct Line instance for that line in the cache
      struct Line *line = &cache->lines[i];
      // Access the data elements from the struct Line instance
      unsigned char *data = line->data;
      // Print out the line and corresponding values
      printf("set: %x - tag: %x - valid: %u - data %.2x %.2x %.2x %.2x\n",
              i, line->tag, line->valid, data[0], data[1], data[2], data[3]);
    }
  }
}

void readValue(struct Cache *cache, unsigned int address){
  // Calculate the set and tag for the address
  unsigned int s = getSet(address);
  unsigned int t = getTag(address);

  // Display output for the address being searched for
  printf("looking for set: %x - tag: %x\n", s, t);

  // Iterate through the whole cache
  for(int i = 0; i < cache->numLines; i++){
    // Check if Set is in the cache
    if(i == s){

      // If the line at position i is invalid, we have a cold miss
      if(cache->lines[i].valid == 0){
        // Print the notification of the cold miss
        printf("no valid line found - cold miss!\n");
        // Exit the loop
        break;

      // If line is valid
      }else{
        // Get the offset of the address
        unsigned int o = getOffset(address);
        // Create struct Line for line at poistion i in cache
        struct Line *line = &cache->lines[i];
        // Construct pointer to data elements of struct Line
        unsigned char *data = line->data;

        // Print associated values of the line found
        printf("found set: %x - tag: %x - offset: %x - valid: %u - data: %.2x\n",
                i, line->tag, o, line->valid, data[0]);

        // If the tag of the found line does not match tag of address there is
        // a conflict miss
        if(line->tag != t){
          // Print notification of the conflict miss
          printf("tag mismatch - conflict miss!\n");
          // exit loop
          break;

        // If line is valid and tags match, we have a hit
        }else{
          // Print notification of the hit
          printf("hit!\n");
          // Exit out of the loop
          break;
        }
      }
    }
  }
}

void writeValue(struct Cache *cache, unsigned int address, unsigned char *newData){
  // Calculate set and tag for address
  unsigned int s = getSet(address);
  unsigned int t = getTag(address);

  // Get pointer to cache line in the specified set
  struct Line *line = &cache->lines[s];

  // Determine if we have a valid line in the cache that does not contain the
  // specified address - we detect this by checking for a tag mismatch.
  if(line->valid && line->tag != t){
    unsigned char *data = line->data;
    printf("evicting line - set: %x - tag: %x - valid: %u - data: %.2x %.2x %.2x %.2x\n",
            s, line->tag, line->valid, data[0], data[1], data[2], data[3]);
  }

  // Copy new data to line (could use memcpy here instead)
  for(int i = 0; i < 4; ++i){
    line->data[i] = newData[i];
  }

  // Update line tag, mark line as valid
  line->tag = t;
  line->valid = 1;

  printf("wrote set: %x - tag: %x - valid: %u - data: %.2x %.2x %.2x %.2x\n",
          s, line->tag, line->valid, newData[0], newData[1], newData[2], newData[3]);
}

int main(){
  struct Cache *cache = mallocCache(16);

  // Loop until user enters 'q'
  char c;
  do{
    printf("Enter 'r' for read, 'w' for write, 'p' to print, 'q' to quit: ");
    scanf(" %c", &c);

    if(c=='r'){
      printf("Enter 32-bit unsigned hex address: ");

      unsigned int a;
      scanf(" %x", &a);

      readValue(cache, a);
    } else if (c == 'w'){
      printf("Enter 32-bit unsigned hex address: ");

      unsigned int a;
      scanf(" %x", &a);

      printf("Enter 32-bit unsigned hex value: ");

      unsigned int v;
      scanf(" %x", &v);

      // Get byte pointer to v
      unsigned char *data = (unsigned char *)&v;

      writeValue(cache, a, data);
    } else if (c == 'p'){
      printCache(cache);
    }
  }while (c != 'q');
  freeCache(cache);
}
