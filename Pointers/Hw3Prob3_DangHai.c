/* This program creates two matrices of random floating point values and multiples them together
 * via use of the pointer to pointer concept. 
 *
 * Note:
 * 		sample command: ./a.out 3 4 3
 *              	                m n p
 * Also:  (m x n) * (n x p) = (m x p)    
 */
#include <stdio.h>
#include <stdlib.h>

//Function prototypes
void createArray(float**, int, int);
void fillArray(float**, int, int);
void multiply(float**, float**, float**, int, int, int);


/*****************************************************************************************
 * The main function takes in arguments and calls the createArray(), fillArray(),        *
 * and multiply() methods to create a 2 dimensional array, fill it with random floating  *
 * point numbers, and then multiplies the two created arrays into a new array.           *
 *****************************************************************************************/
int main(int argc, char* argv[])
{
    //Take in arguments from terminal and convert from char to int 
    int m, n, p;
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    p = atoi(argv[3]);
    
    if (n != 0 && m != 0 && p != 0 )   		//if the matrices aren't 0-dimensional
    {
    	float **a, **b, **mult;
    
    	a = malloc(sizeof(int*) * m);   	//Create space in memory for m pointers 
    	createArray(a, m, n);			//Create the 2d array by having each pointer 
						//point to another set of pointers in memory
    	printf("\na =  \n");		
    	fillArray(a, m, n);			//fill the array with random float entries

    
    	b = malloc(sizeof(int*) * n);		//Create space in memory for n pointers 
    	createArray(b, n, p);			//Create the 2d array by having each pointer 
						//point to another set of pointers in memory
    	printf("\nb = \n");
    	fillArray(b, n, p);			//fill the array with random float entries

    
    	mult = malloc(sizeof(int*) * m);	//Create space in memory for m pointers 
    	createArray(mult, m, p);		//Create the 2d array by having each pointer 
						//point to another set of pointers in memory
    	printf("\n\na * b = \n");
    	multiply(a, b, mult, m, n, p);		//multiply matrix a and b and store in mult
    

    	//free space in memory to prevent memory leakage 
    	//(not sure if this is the correct technique)
    	free(a);
    	free(b);
    	free(mult);				//one of the dimensions of the matrices are of 0-dim
    } else { 
      printf("   {0}    set is empty (0-dimensional)\n");
    }
    return 0;
}

/*****************************************************************************************
 * This function helps create the 2-dimesional array via pointers to pointers.           *
 * In main(), pointers in memory are made. Here, each pointer from main() now points to  *
 * an entire new set/row of pointers. Technically it simulates a 2-d array via pointers. *
 *****************************************************************************************/
void createArray(float **b, int row, int col)
{
    int i;
    for(i = 0; i < row; i++)
    {
        //for each pointer, create space in memory for # of col pointers 
        *(b+i) = malloc(sizeof(int*) * col); 
    }
}

/***************************************************************************************
 * The fillArray() funciton takes the passed 2-dimensional array starting address and  *
 * and populates the array with random floating point numbers and printed out.         *
 ***************************************************************************************/
void fillArray(float **b, int row, int col)
{
     int i, j;
     for(i = 0; i < row; i++)
       for(j = 0; j < col; j++){
           b[i][j] = 10.0 * (float)rand()/(float)(RAND_MAX);	 //10 * [0.0 to 1.0]
           printf("%3.2f ", b[i][j]);
           if(j == col - 1)   		//when matrix reaches the end of its col, do a new line
              printf("\n");
       }
}

/***********************************************************************************
 * This function takes in the array of pointers to pointers and multiples the two  *
 * matrices into a new matrix which is stored in mult.                             *
 ***********************************************************************************/
void multiply(float **a, float **b, float **mult, int m, int n, int p)
{
    int i, j, k;
    float sum;

    for(i = 0; i < m; i++){                 //represents outer m
        for(k = 0; k < p; k++){             //represents outer k
            sum = 0.0;			    //at each iteration zero out sum
            for(j = 0; j < n; j++){	    //represents inner product, n
    	        sum += a[i][j]*b[j][k];     //(row of matrix a) * (column of matrix b) 
            }
            mult[i][k] = sum;               //assign multipled entry into mult array		
            printf("%10.2f", mult[i][k]);   //print out new matrix in mult
            if(k == p-1)
               printf("\n");  
        }
    }
}


