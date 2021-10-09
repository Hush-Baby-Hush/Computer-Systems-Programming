#include <stdio.h>
#include "prime.h"

int main(){
  // Write the code to take a number n from user and print all the prime numbers between 1 and n
  int number;
  printf("Enter the value of n: ");
  scanf("%d", & number);
  printf("Printing primes less than or equal to 30:\n");
  for(int i=2; i<number; i++)
  {
    if(is_prime(i))
    {
      printf("%d ", i);
    }
  }

  return 0;
}

