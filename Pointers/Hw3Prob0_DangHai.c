/*
 * This program takes two char arrays and concatenates them.
 */

#include <stdio.h>

void strcat2(char*, char*);

int main()
{
   char s[] = "foo";
   char t[] = "bar";
   strcat2(&s[0], &t[0]);
   printf("This is the new one %s\n", s);

   int i;   
   for(i = 0; s[i] != '\0'; i++)		//print out the new concatenated string.
       printf("%c\n", s[i]);
   return 0;
}

/*strcat: concatenate t to end of s; */
void strcat2(char *s, char *t){
    int i;
    //search for end of s, that isn't a null character
    for(i = 0; *s != '\0'; i++, s++)
	printf("%c\n",*s);
 	;
    printf("%d\n", i);		//print out the end location of the current char array
    
    
    //begin concatentation, adding t to the end of s as long as t isn't a null character
    while((*s = *t) != '\0'){
	s++;			//increment the pointer pointing to the addresses of s & t 
        t++;
        printf("%c\n", *s);	//print out the contents
     
    }
    s[i] = '\0';
    
}
