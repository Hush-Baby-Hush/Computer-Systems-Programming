#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){
    int i,j,k;

    for (j = 0; j < cols; j++)
    {
        for (i = 0; i <rows ; i++)
        {
            if (my_array[i*cols+j]!=-1)
            {
                for (k = 0; k < i; k++)
                {
                    if (my_array[k*cols+j]==-1)
                    {
                        my_array[k*cols+j] = my_array[i*cols+j];
                        my_array[i*cols+j] = -1;
                        break;
                    }
                    
                }
                
            }
            
        }
        
    }
    
    return;
}
