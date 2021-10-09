// The program first asks the user to enter a row index (this part has been provided to you) 
// and calculate all coefficients in that row and use the standard 
// function printf to print out the coefficients.  
// We first read a number from the keyboard, and then use the for loop to calculte every coefficient,
// and then print it to the screen. For the index 0, we simply print 1 before the for loop. 

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  unsigned long k = 1;      //k is the coeffient we will calculate. Initialize it to 1 and print it since index 0 will always be 1
  int i;
  printf("%lu ",k);         //print the coefficient of index 0
  for(i=1;i<row+1;i++)      //use for loop to calculate every coefficient
  {
    k = (row+1-i)* k/i;     //use of the equation ∏
    printf("%lu ",k);       //print the ith binomial coefficient in the rowth row. 
  }

  return 0;
}
