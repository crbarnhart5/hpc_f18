#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

   srand(time(NULL));

   int mod = rand() % 1000;
   char str[64];

   sprintf(str, "write_file_%d.txt", mod);
   printf("Writing a file called %s.\n", str);
   
   FILE *fp = fopen(str, "w+");

   fprintf(fp, "mod = %d\n", mod);

   fclose(fp);
}
