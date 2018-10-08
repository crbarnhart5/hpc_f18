/*
 * Hello world using OpenMP
 *
 * J. Hollingsworth
 */
#include <stdio.h>
#include <omp.h>

int main() {
   #pragma omp parallel
   {
   int tid = omp_get_thread_num();
   printf("thread %d says hello, world\n", tid);
   }
}
/* gcc -o hello_openmp hello_openmp -fopenmp */
