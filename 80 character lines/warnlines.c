/* Name: Ritika Sabharwal
   TerpConnect ID: rsabharw
    University ID number: 117272918
    Discussion section: 0107
 */

/* This file reads input from the user and 
prints out the line numbers while indicating
which lines have more than 80 characters.
*/

#include <stdio.h>

int main(void) {
  /*Declarations and Initialization*/
  int count = 1; 
  char input[8000];
  int i = 1;
  int length = 0;
  char character = 'c';
  char first_char = 'f';
  int size = 0;

  while (!feof(stdin))/* checks for the end of the input*/
    {
      i = 1;
      length = 0;
      scanf("%c", &character);
      input[i] = character;
      i++;
      /* checks if the previous character is the newline
	 character to mark the end of the current line.*/
      while (!feof(stdin) && input[i-1] != '\n')
	{	   
	  scanf("%c", &character);
	  /*stores the characters of the current line in the array.*/
	  input[i] = character;
	  i++;
	  length++;
	}
      

      /*checks if the characters read are not empty.
	Manages edge case of zero lines as input.*/
      if(!feof(stdin))
	{
	  size = length;
	  /*size equals length before counting the spaces for tab characters.*/
	  length = 0;
	  /*recalculating length with spaces for tab characters.*/
	  for (i = 1; i < size + 1; i++)
	    { 
	      if (input[i] == '\t')
		length += (8 - (length % 8));
	      else
		length++;
	    }
     
	  /*prints * for lines with more than 80 characters and a  
          space for lines less than 80 characters.*/
	  if (length > 80)
	    first_char = '*';
	  else
	    first_char = ' ';
	  
	  /*prints required output for every line read.*/
	  printf("%c%5d: ", first_char , count);
  
	  for (i = 1; i < size + 1; i++)
	    printf("%c", input[i]);
	
	  /*prints additional line with extra ^ for lines
	    with more than 80 characters.*/
	  if (length > 80)
	   {
	     printf("\n");
	     for (i = 0; i < 88; i++)
	       printf(" ");
	     for (i = 80;i < length ; i++)
	     printf("^");
	   }
	  
	  /*increments count to keep track of the line numbers.*/
	  count++;
	  printf("\n");
	}
    }
  return 0;
}
