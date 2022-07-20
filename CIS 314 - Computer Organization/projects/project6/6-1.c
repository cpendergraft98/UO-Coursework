/*
CIS 314 Project 6, Part 1
Author: Cole Pendergraft
*/

#include <stdio.h>
#include <stdlib.h>

int f(int a, int b, int c, int d, int n){
  int result = 0;
  int ab = a * b; // Initialize a * b outside of loop
  int cd = c * d; // Initialize c * d outside of loop
  for(int i = 0; i< n; i++){
    int icd = 0; // For every iteration of i we want to reset i*c*d = 0
    for (int j =0; j < n; j++){
      result += ab + icd + j;  // Perform calculation. icd = 0 on first iteration
      icd += cd;  // Increment icd by adding cd
    }
  }
  return result;
}

int main(){
  int t1, t2, t3, t4;
  t1 = f(1, 2, 3, 4, 5);
  printf("t1 score %d\n", t1);
  t2 = f(2, 3, 4, 5, 6);
  printf("t2 score %d\n", t2);
  t3 = f(6, 5, 4, 3, 2);
  printf("t3 score %d\n", t3);
  t4 = f(5, 4, 3, 2, 1);
  printf("t4 score %d\n", t4);
  return 0;
}
