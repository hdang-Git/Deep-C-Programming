//This program concatenates string by allocating space in memory and assigning the two char arrays to the allocated space.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mystrcat(char*, char*);


//Sample cmd: "./a.out Hello Bob"
int main(int argc, char *argv[])
{ 
    char* b = mystrcat(argv[1], argv[2]);
    printf("%s\n", b);
    return 0;
}

//Write the following function with test for it. 
/* mystrcat: concatenate t to end of s and returns it  */
char * mystrcat(char *s, char *t) {
     int i = 0;
     int input1 = strlen(s);
     int input2 = strlen(t);
     //allocate space to length of string1 + string2 + \0, all times the size of char
     char* concat = (char *) malloc((input1+input2 + 1) * sizeof(char));
     
     //add input1 to concat
     while(s[i] != '\0')
     {
         concat[i] = s[i];
         i++;
     }
     
     //add input2 to concat
     int j = 0;
     while(t[j] != '\0')
     {
         concat[i] = t[j];
         j++;
         i++;
     }
     concat[i] = '\0';
     
     return concat;
}
