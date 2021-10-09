// in this program we input two values a and b, and print all the semiprime between these two numbers
// We have complete the is_prime and print_semiprimes functions below
// the is_prime function will check if the number between a and b is a prime or not 
// and the print_semiprimes function will print all the semiprimes between a and b 
// We will use is_prime funcion in the print_semiprimes function 
// and we will use the print_semiprimes function in the main function.

#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a, b);  //use print_semiprimes function to print all the semiprimes between a and b
   return 0;
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  for(int i = 2; i<number;i++)  //loop to check all the possible factors
  {
    if(number%i==0)             //check if it can be divided by i
    {
      return 0;                 //if can be divided by i, then it is not prime
    }
  }
  return 1;                     //if no factor, then it is prime

}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int flag = 0;   //here the flag is used to check if the number has been printed or not
  for(int i = a; i<=b; i++)   //loop to check all the numbers between a and b
  {
    flag = 0;     //restore flag to zero
    for(int j = 2; j<i; j++)    //loop to check all the possible factors of i
    {
      if(!flag && i%j==0 && is_prime(j) && is_prime(i/j))   //flag should be 0, indicating hasn't been printed. 
      //i%j==0 is used to check if it can be divided by j; both j and i/j should be prime number
      {
        printf("%d ", i);   //print i if it meet all the four requirement above
        flag = 1;   //since it is printed, flag becomes 1
      }
    }
  }
  if(flag)    //if flag ==1, means there are semiprimes been printed
  {
    return 1;
  }
  else
  {
    return 0;   //else no print, retrun 0
  }
  
}



