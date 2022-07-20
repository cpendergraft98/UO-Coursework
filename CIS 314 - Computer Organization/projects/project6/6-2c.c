/*
CIS 314 Project 6, Part 2-c
Author: Cole Pendergraft
*/
// We need to set a limit of length - 3 because we are performing four
// simultaneous calculations compared to our original single calculation.
// Originally when we had 1 calculation, we iterated length number of times,
// but now we have 3 additional calculations being performed, so we want
// to iterate length - 3 times.
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void inner(float *u, float *v, int length, float *dest) {
  int i;
  float sum = 0.0f;

  for (i = 0; i < length; ++i) {
    sum += u[i] * v[i];
  }

  *dest = sum;
}

void inner2(float *u, float *v, int length, float *dest){
  int i;

  int limit = length - 3;

  // Four parallel accumulators
  float sum1 = 0.0f;
  float sum2 = 0.0f;
  float sum3 = 0.0f;
  float sum4 = 0.0f;

  // Loop unrolling into four calculations instead of 1
  for(i = 0; i < limit; i += 4){  // Iterate by four each time to account for
                                  // four simultaneous calculations.
    sum1 += u[i] * v[i];
    sum2 += u[i+1] * v[i+1];
    sum3 += u[i+2] * v[i+2];
    sum4 += u[i+3] * v[i+3];
  }

  for(; i < length; ++i){ // If our length is not a multiple of four, we have
                          // some remaining elements to take care of. We can
                          // add these into any of our other sums.
    sum1 += u[i] * v[i];
  }

  *dest = sum1 + sum2 + sum3 + sum4;  // Sum up all of our accumlators
}


int main(){
  int size = 100;
  float u[size];  // Initialize array u
  float v[size];  // Initialize array v
  float dest[size]; // Initialize destination array

  clock_t start = clock();  // Start timer
  //printf("Start time: %ld\n", start); // Used for debugging
  inner(u, v, size, dest); // Execute inner
  clock_t end = clock();  // End timer
  //printf("End time: %ld\n", end); // Used for debugging
  double time1 = (double)(end - start) / CLOCKS_PER_SEC;  // Compute time
  printf("Inner time: %.10lf\n", time1);  // Print time for checking

  start = clock();  // Restart timer
  //printf("Start time: %ld\n", start); // Used for debugging
  inner2(u, v, size, dest);  // Execute inner2
  end = clock();  // End timer
  //printf("End time: %ld\n", end); // Used for debugging
  double time2 = (double)(end - start) / CLOCKS_PER_SEC;  // Compute time
  printf("Inner2 time: %.10lf\n", time2); // Print time for checking

  return 0;
}
