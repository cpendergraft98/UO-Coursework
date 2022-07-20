/*
CIS 314 Project 6, Part 3
Author: Cole Pendergraft
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float f(float *a, int n) {
  float prod = 1.0f;
  for (int i = 0; i < n; ++i) {
    if (a[i] != 0.0f) {
      prod *= a[i];
    }
  }
  return prod;
}

float g(float *a, int n) {
  float prod = 1.0f;
  for (int i = 0; i < n; ++i) {
    prod *= a[i]; // Just removed the if statement
  }
  return prod;
}

float* createArray(int size) {
  float *a = (float *)malloc(size * sizeof(float));
  for (int i = 0; i < size; ++i) {
    // 50% chance that a[i] is 0.0f, random value on the range
    // [0.76, 1.26] otherwise.
    float r = rand()/(float)RAND_MAX;
    a[i] = r < 0.5f ? 0.0f : r + 0.26f;
  }
  return a;
}

int main(){
  int size = 10000;
  float *a = createArray(size);

  float b[size];  // Create an array B that matches the size of A
  int aNonZcount = 0; // Create a counter to store the number of nonzero elements
                      // in A. This will be used to create array C
  for(int i = 0; i < size; i++){
    if(a[i] == 0.0f){ // If the element at i in A is zero
      b[i] = 1.0f;  // Set the element in the same position in B to be 1
    }else{  // Otherwise
      b[i] = a[i];  // The element at position i in B should match that of A
      aNonZcount += 1;  // Increment our counter of nonzero objects in A
    }
  }

  float c[aNonZcount];  // Create an array C that matches the size of the total
                        // number of nonzero elements in A.
  int cPosCount = 0;    // Create a position tracker that will be used to
                        // determine insertion points of C.
  for(int i = 0; i < size; i++){
    if(a[i] != 0.0f){ // If the element in A at i is nonzero
      c[cPosCount] = a[i];  // We want to set the element in C at the cPosCount
                            // to match the element in A. This means the first
                            // non zero ele in A will be at pos 0 in C, the
                            // second non zero ele in A will be at pos 1 in
                            // C, and so on.
      cPosCount += 1;       // Increment our position tracker
    }
  }


  // Everything from here on out is just the clock logic
  clock_t start = clock();
  float prod1 = f(a, size);
  clock_t end = clock();
  double time1 = (double)(end - start) / CLOCKS_PER_SEC;

  printf("Product1 f(a): %lf\n", prod1);
  printf("Time1 f(a): %lf\n", time1);

  start = clock();
  float prod2 = g(b, size);
  end = clock();
  double time2 = (double)(end - start) / CLOCKS_PER_SEC;

  printf("Product2 g(b): %lf\n", prod2);
  printf("Time2 g(b): %lf\n", time2);

  /*
  part b) I found that the computation for part b was faster than that for part
  a. I believe this is due to the removal of the if statement that was used in
  the f version of the funciton. Since we now have no 0 elements in B, we no
  longer need to check for 0 values, which removes a time consuming step from
  f. This means that the time improvements stem from the changes we made to f
  and not the changes we made to B. Rather, the changes we made to B were only
  done so that our new g function would work without multiplying by 0.
  */

  start = clock();
  float prod3 = g(c, aNonZcount);
  end = clock();
  double time3 = (double)(end - start) / CLOCKS_PER_SEC;

  printf("Product3 g(b): %lf\n", prod3);
  printf("Time3 g(b): %lf\n", time3);

  /*
  part c) I found that the computation for part c was even faster than that in
  part b. I believe this is because the computation in part c has all the same
  speed improvements as part b does, but then we also just remove any 0 element instead
  of converting it to 1. This means that while B still has to perform multiplications
  by 1 where A originally had a 0 element, C doesn't have to do anything because
  that 0 element in A is non existant in C. Not needing to perform those mults
  reduces the number of operations performed and improves the time.
  */

  free(a);  // I found that if I also have a free(b) and free(c) I get a
            // segmentation fault, so I only have free(a)

  return 0;
}
