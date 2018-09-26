#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ITERATIONS 100000000

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

int main() {

  // start timing
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  int inside = 0;

  for (int i = 0; i < ITERATIONS; i++) {
    // throw a random dart
    double x = arc4random_uniform(RAND_MAX)/(double)RAND_MAX;
    double y = arc4random_uniform(RAND_MAX)/(double)RAND_MAX;

    // is the dart inside the circle?
    double dist = distance(0, 0, x, y);
    if (dist < 1.0) {
      inside++;
    }
  }

  // stop timing
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  // compute elapsed time (ms)
  unsigned long long delta_ms = (end.tv_sec - start.tv_sec) * 1000 +
      (end.tv_nsec - start.tv_nsec) / 1000000;
  printf("elpased time: %llu ms\n", delta_ms);

  printf("Iterations: %d ==> %g\n", ITERATIONS, inside/(double)ITERATIONS*4);

}
