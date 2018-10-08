#include <stdio.h>

int main() {
      
   FILE *fp = fopen("10_ints_under_1000.txt", "r");

   int num;
   while (fscanf(fp, "%d", &num) != EOF) {
      printf("num: %d\n", num);
   }

   fclose(fp);
}
