/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n)
{
//YOUR CODE HERE
    for(int i = 0; i <m; i++)
    {
        for(int p = 0; p<n; p++)
        {
            double sum = 0;
            for(int j = 0; j<k; j++)
            {
                // sum += (*(matrixA+i*k+j))*(*(matrixB+j*n+p));
                sum += matrixA[i*k+j]*matrixB[j*n+p];
            }
            // *(matrixC+i*n+p)=sum;
            matrixC[i*n+p] = sum;
        }
    }
    return;
}

