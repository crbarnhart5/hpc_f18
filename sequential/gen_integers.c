#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

   int count = atoi(argv[1]);
   int max = atoi(argv[2]);

   srand(time(NULL));

   for (int i = 0; i < count; i++) {
      printf("%d\n", rand() % max);
   }
}
