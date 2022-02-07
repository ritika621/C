#include <stdio.h>
#include <pthread.h>
#include "randomdelay.h"
#include <stdlib.h>

/*Name:  Ritika Sabharwal
TerpConnect ID: rsabharw
University ID: 117272918
Discussion Section: 0107

I pledge on my honor that I have not given or received any
unauthorized assistance on this assignment
*/

/* This program processes a list of zero or more files whose names are given
 * on its command line, counting the number of lines that each file contains
 * that are longer than 80 characters.  It aggregates the number of lines in
 * all the files that are longer than 80 characters and prints the total as
 * its only output.  Files are read one character at a time, by character, *
 * because we don't have any way to know the maximum length of lines.  More
 * realistically, and unlike Project #2, we do not require that the last
 * line of a file end with a newline.
 */

static void *line_count(void *file);
int main(int argc, char *argv[])
{
  long count = 0;
  pthread_t *tids = malloc(sizeof(pthread_t) * (argc - 1));
  void *num = NULL;
  int i  = 0;
  
  if (argc > 1)
    {
 
      for (i = 0; i< argc - 1; i++)
	pthread_create(&tids[i], NULL, line_count, argv[i + 1]);
      
      i = 0;

      for(i = 0; i< argc - 1; i++)
	{
	  pthread_join(tids[i], &num);
	  count += * (long *) num;
	  free(num);
	  num = NULL;
	}

      free(tids);
      tids = NULL;
  
      printf("%ld\n", count);
 
}
  return 0;
} 

static void *line_count(void *file)
{

  long one_file_count = 0, line_length = 0;
  long *return_lines = malloc(sizeof(*return_lines));  
  char ch;
  FILE *fp;
  char *file_name;
  
  file_name = (char *) file;
  
  fp= fopen(file_name, "r");  /* open file for reading */

      /* silently ignore nonexistent files, or ones that there was an error
         trying to open */
  if (fp != NULL) 
    {
      one_file_count= 0;
      line_length= 0;

        /* see the explanation in the project assignment regarding what this
           is for */
      /* randomdelay(file_name);*/

       while ((ch= fgetc(fp)) != EOF)
	 {  /* read by character */
	   if (ch != '\n')
	     line_length++;
	   else {
            if (line_length > 80)
	      one_file_count++;

            line_length= 0;  /* reset for the next line */
          }
        }

        /* we have to handle it as a special case if the last line does not
           end with a newline and it is longer than 80 characters (of course
           only the last line can possibly not end with a newline) */
        if (line_length > 80)
          one_file_count++;
 
	fclose(fp);
    }
      else
	one_file_count = 0;
  *return_lines = one_file_count;     
  return return_lines;
}
