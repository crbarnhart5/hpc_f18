#include <stdio.h>
#include <math.h>

#define HOWMANY 35

int countDigits(unsigned long long num) {
  int count = 0;
  while (num > 0) {
    num /= 10;
    count++;
  }
  return count;
}

int isNarcissistic(unsigned long long num) {
  int power = countDigits(num);
  int sum = 0;
  unsigned long long saved_num = num;
  while (num > 0) {
    int digit = num % 10;
    num /= 10;
    sum += pow(digit, power);
  }
  //printf("sum: %d, num: %d\n", sum, num);
  return (sum == saved_num);
}

int main() {
  int count = 0;
  unsigned long long num = 1;
  while (count < HOWMANY) {
    if (isNarcissistic(num)) {
      printf("%llu\n", num);
      count++;
    }
    num++;
  }
}
