#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define ITERATIONS 100000000
#define NUM_THREADS 4

int global_inside[NUM_THREADS];

double distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

void *monte_carlo_loop(void * thread_id) {
   int tid = (int)(long) thread_id;


  int inside = 0;
  for (int i = 0; i < ITERATIONS/NUM_THREADS; i++) {
    // throw a random dart
    //double x = arc4random_uniform(RAND_MAX)/(double)RAND_MAX;
    //double y = arc4random_uniform(RAND_MAX)/(double)RAND_MAX;
    double x = rand()/(double)RAND_MAX;
    double y = rand()/(double)RAND_MAX;

    // is the dart inside the circle?
    double dist = distance(0, 0, x, y);
    if (dist < 1.0) {
      inside++;
    }
  }

  global_inside[tid] = inside;

  pthread_exit(NULL);
}

int main() {

  srand(time(NULL));

  // start timing
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

  pthread_t threads[NUM_THREADS];

  for (int t = 0; t < NUM_THREADS; t++) {
      global_inside[t] = 0;
      int rc = pthread_create(&threads[t], NULL, monte_carlo_loop, (void *)(long) t);
      if (rc) {
         fprintf(stderr, "Uh oh!\n");
         exit(-1);
      }
  }

  // wait for all threads to finish
  for (int t = 0; t < NUM_THREADS; t++) {
     pthread_join(threads[t], NULL);
  }

  // sum up the array of inside values
  int sum = 0;
  for (int t = 0 ; t < NUM_THREADS; t++) {
     sum += global_inside[t];
  }

  // stop timing
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  // compute elapsed time (ms)
  unsigned long long delta_ms = (end.tv_sec - start.tv_sec) * 1000 +
      (end.tv_nsec - start.tv_nsec) / 1000000;
  printf("elpased time: %llu ms\n", delta_ms);

  printf("Iterations: %d ==> %g\n", ITERATIONS, sum/(double)ITERATIONS*4);

}

