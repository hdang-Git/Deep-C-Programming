/*  This program generates a text file of random student first, last names, ID numbers, and GPAs. 
 *
 *	  Note:
 *		  Sample cmd input: ./a.out 100 output.txt
 */

#include <stdio.h>
#include <stdlib.h>

//Function Prototypes
int ctoi(char*);
void generate(int, char[]);

//array of random names
char fnames[][10] = {"Mary", "Bob", "Bruce", "Jack","John", "Oliver", 
		     "Sarah", "Barry", "Clark", "Harrison", "Marie"};

char lnames[][10] = {"Wayne", "Kent", "Jane", "Blah", "Smith", "Wilson", 
		     "Allen", "Queen", "Lee", "Curie", "Wells"};


/***********************************************************************************************
 * This function takes in arguments from the terminal and calls the ctoi and generate function.*
 ***********************************************************************************************/
int main(int argc, char *argv[])		
{
   int a = ctoi(argv[1]);  //argv[1] is the number entered 	Ex.  100
   generate(a, argv[2]);   //argv[2] is the filename entered 	Ex.  output.txt
   return 0;
}


/*******************************************************************************************
 * This is merely a copy of atoi which converts char arrays to ints. It was looked up and  *
 * replicated for study.The function atoi could have been used instead, but for study, it  *
 * was loosely implemented without input-validation.                                       *
 *******************************************************************************************/
int ctoi(char* str)
{
    if(!str)					//if not a character array
       printf("Check again"); 
    int num = 0;
    char* ch = str;
    while((*ch >= '0') && (*ch <= '9'))		//as long as value in ch is between '0' and '9'
    {
        num = (10 * num) + (*ch-'0');		//add new value in the ones place, while shifting
						//prev value to the next tens place 
        ch++;					//increment pointer to char array
    }
    return num;
}



/**********************************************************************************************
 * This function creates random ids and gpas,and randomly selects a first and last name from  *
 * the arrays. Then, the function prints it to an output file given by argv[2];               *
 **********************************************************************************************/
void generate(int num, char name[])
{
    FILE *f;
    unsigned int ID, i;
    float GPA;

    f = fopen(name, "w");				//open a file and write to it

    //loop for # of input elements 
    for(i = 0; i < num; i++)
    {
	ID = rand() % 100000 + 1;		 
        GPA = (float)rand() / (float)(RAND_MAX) * 4;	//4 * [0 to 1] inclusive

        fprintf(f, "%9s %7s %6d %4.2f\n", (fnames[rand()%10 + 1]), 
				(lnames[rand()%10 + 1]), ID, GPA);	//print to file 
    } 
    fclose(f);
}

