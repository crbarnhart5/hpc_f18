/*
 * Use OpenMP to parallelize a loop
 *
 * J. Hollingsworth
 */
#include <stdio.h>
#include <omp.h>

#define N 100

int main() {

   double a[N], b[N], result[N];

   // initialize
   for (int i = 0; i < N; i++) {
      a[i] = 1.0 * i;
      b[i] = 2.0 * i;
   }

   #pragma omp parallel for
   for (int i = 0; i < N; i++) {
      result[i] = a[i] + b [i];
   }

   printf("TEST result[19] = %g\n", result[19]);
}
/* gcc -o loop_openmp loop_openmp.c -fopenmp */
