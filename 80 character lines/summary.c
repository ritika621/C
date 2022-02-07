/* Name: Ritika Sabharwal
   TerpConnect login ID: rsabharw
    University ID number: 117272918
     Discussion section : 0107
  */

/* This file prints the summary of all line 
numbers whose characters were greater than 80.*/

#include <stdio.h>

int main(void) {
  /* Declrations and Initializations*/
  int count = 0;
  int numbers[99999];
  int i =0;
  char character = 'm';
  int line_number = 0;

  /*while loop goes on until there is no more input to be read*/
  while (!feof(stdin))
   {
     line_number = 0;
     
     scanf("%c", &character);
     if (character == '*')
      {
	scanf("%5d", &line_number);
	numbers[count] = line_number;
	count++;

	/*reads the rest of the line*/
	while (character != '\n')
	  scanf("%c", &character);
	
	/*skips the next line*/
	scanf("%c", &character);
       }
   }
      
  /*prints a space after every line number except for
    the first and last line numbers.*/
   if (count != 0)
     {
       for(i = 0;  i< count; i++)
	 {
	   if(i != 0 || i != count - 1)
	     printf("%d ", numbers[i]);
	   else
	     printf("%d", numbers[i]);
	 }
     }

    printf("\n");
    return 0;
}
