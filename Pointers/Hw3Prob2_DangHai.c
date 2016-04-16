/*
 * This program uses the student records from part 1 and reads in a file into a 
 * struct array. It then calculates the maximum, minimum, and average GPA.
 * Following this, it is sorted according to last name and printed to an output file.
 * 
 *   Note:
 *       sample cmd: analyzeRecords output.txt 100 sorted.txt 
 *       Ex:   ./a.out output.txt 100 sorted.txt
 */

#include <stdio.h>
#include "recordGen.h"

//function prototypes
void readFile(int, char[], struct StudentRecord*);
void report(float*, float*, float*, int, struct StudentRecord*);
void sort(struct StudentRecord*, int);
int strcomp(char[], char[]);
void writeFile(char[], struct StudentRecord*, int);




/*****************************************************************************************
 *This function stores the argument vecots, creates a struct, and calls a method to read *
 *in a file, find the max, min & avg of the file, sort the file, and write the sorted    *
 *struct to a file.                                                                      *
 *****************************************************************************************/
int main(int argc, char* argv[])
{
   float max, min, avg;

   char* strIn = argv[1];			//argv[1] is input filename    Ex. output.txt
   int lines = atoi(argv[2]);   		//argv[2] is number of lines   Ex. 100
   char* strOut = argv[3];			//argv[3] is output filename   Ex. sorted.txt

   struct StudentRecord record[lines];		//Create a struct array of student records

   readFile(lines, strIn, record);		//Call readFile() to read in file to struct array
   report(&max, &min, &avg, lines, record);	//Call report() to calculate max, min, & avg
   sort(record, lines);				//Call sort() to sort file by last names
   writeFile(strOut, record, lines);		//Call writeFile() to write sorted file to new file 

   //print out results of max, min, and avg from report()
   printf("\n\nmax: %.2f, min: %.2f, avg: %.2f\n\n\n", max, min, avg);	 
   return 0;
}

/****************************************************************************************
 *This function reads in a file and stores it into a struct. It also checks if the file *
 *exists or not.                                                                        *
 ****************************************************************************************/
void readFile(int lines, char input[], struct StudentRecord* record)
{
    int i;

    FILE *in;
    if((in = fopen(input, "r")) == NULL)	//if file doesn't exist (NULL) then print error msg
    {
       printf("Error opening file.\n");
    }
    //Assuming that the # of lines is known by the user, 
    //a definite loop is used rather than an indefinite loop
    for(i = 0; i < lines; i++)		
    {
	    //read the file data into the struct array record
            fscanf(in, "%9s %9s %5d %4f\n", record[i].firstname, record[i].lastname, 
                                            &record[i].ID, &record[i].GPA);

/*	    //This is to check to make sure file is being read by printing to terminal.
            printf("%s %s %d %.2f\n", record[i].firstname, record[i].lastname, 
                                      record[i].ID, record[i].GPA);
*/
    }
}


/*************************************************************************************
 *This function calculates the maximum, minimum, and the average GPA using pointers. *
 *************************************************************************************/
void report(float* max, float* min, float* avg, int lines, struct StudentRecord* record)
{
    int i;
    float sum;
    sum = *max = *min = record[0].GPA;		//Assign all contents to first GPA element of 
						//struct array StudentRecord
    for(i = 1; i < lines; i++)
    {
        if(record[i].GPA > *max)		//if current GPA is greater than max, reassign max
            *max = record[i].GPA;		
        if(record[i].GPA < *min)		//if current GPA is less than min, reassign min
            *min = record[i].GPA;
        sum += record[i].GPA;			//accumulate the gpa scores
    }
    *avg = sum / (float)lines;			//divide the gpa scores by # of entries to get average
}

/****************************************************************************************
 *This function uses an insertion sort to sort the struct array according to last name. *
 *It could have further been organized by first name as well but time constraints       *
 *prevented otherwise.                                                                  *
 ****************************************************************************************/
void sort(struct StudentRecord *record, int lines)
{
    int i, j;
    struct StudentRecord temp;
    for(i = 1; i < lines - 1; i++)	   //or i = 0 note to self, relook later
    {
       j = i;
       //while index isn't out of bounds & (record[j+1] - record[j]) < 0  
       //where record[j+1] is a smaller character value than record[j] 
       while(j >= 0 && strcomp(record[j+1].lastname, record[j].lastname) < 0)  
       {  
           temp = record[j];				//swap array contents
           record[j] = record[j+1];
           record[j+1] = temp;
           j--;
       }
    }  
    
    //print sorted array
    for(i = 0; i < lines; i++)
    	printf("%s %s %d %.2f\n", record[i].firstname, record[i].lastname, 
                                  record[i].ID, record[i].GPA);
}


/******************************************************************************************
 *This function compares two character arrays/strings by returning the difference of the  *
 *two inputs if they aren't the same or returning -1 if the strings are exactly the same. *
 ******************************************************************************************/
int strcomp(char str1[], char str2[])
{
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') //as long as either strings aren't at the null character 
    {
       if(str1[i] != str2[i])		//if character from str1 is differnt from character of str2
          return str1[i] - str2[i];	//return the difference as an integer 
       i++;
    }
    return -1;				//return -1 if they are completely the same
}

/*****************************************************************
 *This function writes the sorted struct array to an output file *
 *****************************************************************/
void writeFile(char name[], struct StudentRecord *record, int lines)
{
   int i;
   FILE *output;
   output = fopen(name, "w");			
   for(i = 0; i < lines; i++){
      fprintf(output, "%9s %9s %5d %5.2f\n", record[i].firstname, record[i].lastname, 
                                       record[i].ID, record[i].GPA);
   }
   fclose(output);  
}

