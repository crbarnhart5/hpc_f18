/*
 * Sieve of Eratosthenes (sequential)
 * Joel Hollingsworth
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VALUE 10000

int main() {

   // allocate an array large enough to hold all integers
   int * values = (int *)malloc(sizeof(int) * (MAX_VALUE + 1));

   // set the entire array to TRUE
   for (int i = 2; i <= MAX_VALUE; i++) {
      values[i] = 1;
   }

   // start with 2
   int next_prime = 2;

   while (next_prime < sqrt(MAX_VALUE)) {
      // mark of multiples of the prime number
      for (int i = next_prime * 2; i <= MAX_VALUE; i+=next_prime) {
         values[i] = 0;
      }

      // find the next prime
      next_prime++;
      while (values[next_prime] != 1 && next_prime < sqrt(MAX_VALUE)) {
         next_prime++;
      }
   }

   // display the primes and how many found
   int count = 0;
   for (int i = 2; i <= MAX_VALUE; i++) {
      if (values[i] == 1) {
         //printf("%d\n", i);
         count++;
      }
   }

   printf("Found %d primes\n", count);
}
/* gcc -o sieve_of_eratosthenes sieve_of_eratosthenes.c -lm */
