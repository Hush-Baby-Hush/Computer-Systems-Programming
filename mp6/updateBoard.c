// solo life
// Introduction: In this file, there are three functions. The function countLiveNeighbor 
// count the number of live neighbors of the current point.
// The function updateBoard update the board in the next step. 
// The function aliveStable check if the board will not change again. 




/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int live_neighbors = 0;
    int i,j;
    for(i = row-1; i<=row+1; i++)   //check only the surronding point
    {
        if(i<boardRowSize && i>=0)  //check if the row is in the valid range
        {
            for(j = col-1; j<= col+1; j++)  //check only the surronding point
            {
                if(j<boardColSize && j>=0)  //check if the column if in the valid range
                {
                    if(i== row && j==col)
                    {
                        continue;       //jump the point
                    }
                    else
                    {
                        if(board[i*boardColSize+j]==1)  //if the surronding is alive, increase by 1
                        {
                            live_neighbors++;
                        }
                    }
                    
                }
            }
        }
    }
    return live_neighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int i,j,k;
    int count;
    int array[boardRowSize*boardColSize];   //use this array to record change, to avoid change the original array
    for(i = 0; i<boardRowSize; i++)
    {
        for(j = 0; j<boardColSize; j++)
        {
            count = countLiveNeighbor(board,boardRowSize,boardColSize,i,j); //count = the number of alive neighbors
            array[i*boardColSize+j]=board[i*boardColSize+j];    //copy 
            if(board[i*boardColSize+j]==1)
            {
                if(count ==2 || count ==3)
                {
                    continue;   //do nothing
                }
                else
                {
                    array[i*boardColSize+j]= 0; //record change into new array instead of change the original array
                }
                
            }
            else
            {
                if(count==3)
                {
                    array[i*boardColSize+j]= 1;
                }
            }
            
        }
    }
    for(k = 0; k<boardRowSize*boardColSize; k++)    //copy every point in the temporary array into the original array after all the loop
    {
        board[k]=array[k];
    }
    return;
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int flag = 0;   //use flag to record change
    int i,j;
    for(i = 0; i<boardRowSize; i++)
    {
        for(j = 0; j<boardColSize; j++)
        {
            int count = countLiveNeighbor(board,boardRowSize,boardColSize,i,j);
            if(board[i*boardColSize+j]==1)
            {
                if(count==2 ||count==3)
                {
                    continue;   //flag will not change if the array don't need to change
                }
                else
                {
                    flag = 1;   //if so, flag will change to indicate change in the original array
                }
                
            }
            else
            {
                if(count==3)
                {
                    flag = 1;
                }
            }
            
        }
    }
    if(flag == 0)   //use flag to determine return value
    {
        return 1;
    }
    else
    {
        return 0;
    }
    

}

				
				
			

