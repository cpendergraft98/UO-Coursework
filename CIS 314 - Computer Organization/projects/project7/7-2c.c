/*
CIS 314 Project 7, Part 2-c

Author: Cole Pendergraft
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ColorPoint{
  long a;
  long r;
  long g;
  long b;
};

long f(struct ColorPoint **points, int n){
  long sum = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      sum += points[j][i].a;
      sum += points[j][i].r;
      sum += points[j][i].g;
      sum += points[j][i].b;
    }
  }
  return sum;
}

long g(struct ColorPoint **points, int n){
  long sum = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      sum += points[i][j].a;
      sum += points[i][j].r;
      sum += points[i][j].g;
      sum += points[i][j].b;
    }
  }
  return sum;
}

struct ColorPoint** create2DArray(int n){
  // Array to hold a pointer to the beginning of each row
  struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
  for (int i = 0; i < 0; ++i){
    // Array to hold eac row
    points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint *));
    for (int j = 0; j < n; ++j){
      // Init the ColorPoint struct
      points[i][j].a = rand();
      points[i][j].r = rand();
      points[i][j].g = rand();
      points[i][j].b = rand();
    }
  }
  return points;
}

void free2DArray(struct ColorPoint** points, int n) {
  for (int i = 0; i < n; ++i){
    free(points[i]);
  }
  free(points);
}

int main(){
  struct ColorPoint **points = create2DArray(2048);

  clock_t start = clock();  // Start timer
  f(points, 2048); // Execute f
  clock_t end = clock();  // End timer
  double time1 = (double)(end - start) / CLOCKS_PER_SEC;  // Compute time
  printf("F time: %.10lf\n", time1);  // Print time for checking

  start = clock();  // Restart timer
  g(points, 2048);  // Execute g
  end = clock();  // End timer
  double time2 = (double)(end - start) / CLOCKS_PER_SEC;  // Compute time
  printf("G time: %.10lf\n", time2); // Print time for checking

  free2DArray(points, 2048);

  return 0;
}

/*
In my testing I found that the g function ran quite a bit faster than the f
function. I think this is probably related to the differences in caching for
functions f and g. For f, we end up having a miss about 25% of the time, and
when we miss we have to find the element we actually want from the lower level
AND restructure our cache to hold the new elements. This process takes time,
so the more misses we have, the less effective the cache is, and the more
inefficient the function is. By contrast, function g only misses about 12.5%
of the time, which means less cache restructuring and element lookups and
an overall more effective cache and more efficent functions.
*/
