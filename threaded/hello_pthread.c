#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8

void *print_hello(void *thread_id) {
   int tid = (int)(long) thread_id;
   printf("hello, world! It's me, thread %d\n", tid);
   fflush(NULL);
   pthread_exit(NULL);
}

int main() {
   pthread_t threads[NUM_THREADS];

   for (int t = 0; t < NUM_THREADS; t++) {
      printf("In main: creating threads %d\n", t);

      int rc = pthread_create(&threads[t], NULL, print_hello, (void *)(long) t);
      if (rc) {
         fprintf(stderr, "ERROR: return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
}
