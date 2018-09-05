#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITERATIONS 1000000000

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

int main() {

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

  printf("Iterations: %d ==> %g\n", ITERATIONS, inside/(double)ITERATIONS*4);

}
