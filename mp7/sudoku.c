#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

//solo life
//introduction: In this program I wrote five functions. Function is_val_in_row is used to check if there is a same value in the same row.
//Function is_val_in_col is used to check if there is a same value in the same column. Function is_val_in_3x3_zone is used to check if 
//there is a same value in the 3*3 zone. Function is_val_valid is used to check if the value can be put there. It is valid when the above
//three function all output 0 which mean no same value in the same row, column, and zone. 
//In function solve_sudoku we use backtrack algorithm to create a valid output. 


// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int k =0;k<9;k++)
  {
    if(sudoku[i][k]==val) //see if in row i there is a same value. 
    {
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int k =0;k<9;k++)
  {
    if(sudoku[k][j]==val) //see if in column j there is a same value
    {
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  for(int m = i-i%3; m < i+3-i%3;m++) //the zone start from row i-i%3 and end at i+2-i%3
  {
    for(int n = j-j%3; n<j+3-j%3;n++) //the zone start from column j-j%3 and end at j+2-j%3
    {
      if(sudoku[m][n]==val) //see if there is a same value in the 3*3 zone. 
      {
        return 1;
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(!is_val_in_row(val,i,sudoku)&&!is_val_in_col(val,j,sudoku)&&!is_val_in_3x3_zone(val,i,j,sudoku)) //if all the three function's output is 0, it is valid. 
  {
    return 1;
  }
  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;  //initialize row i and colomn j. 
  int flag = 0; //flag is used to check if all the value in the sudoku aren't 0
  for(int k =0;k<81;k++)  //loop though all the 81 cell in the sudoku
  {
    if(sudoku[k/9][k-(k/9)*9]==0) //the row i can be expressed by k/9, and the column can be expressed by k-i*9
    {
      i = k/9;
      j = k-i*9;
      flag = 1; //change flag if we can find one 0. 
      break;  //break the loop to save run-time
    }
  }

  if(flag ==0)
  {
    return 1; //if flag didn't change, indicate all the cell has been set value. 
  }

  for(int num = 1;num<=9;num++) //here use backtrack algorithm. 
  {
    if(is_val_valid(num,i,j,sudoku)==1) //if the value is valid
    {
      sudoku[i][j]=num; //put value in the cell
      if(solve_sudoku(sudoku)==1) //and see if the new sudoku can be solved
      {
        return 1; //if so, return true. 
      }
      sudoku[i][j]=0; //if can't be solved, return to the original sudoku. Clear the current cell. 
    }
  }

  return 0; //If after the for loop can't find a valid sudoku, return false. 
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





