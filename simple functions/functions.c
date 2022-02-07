#include "functions.h"

/* REMOVE THIS COMMENT, then write your implementations of the functions in
 * this source file. 
 * Skeleton versions of the functions already appear below.
 */

/*prism_area calculates the area of a prism given the length, width, and height.*/
int prism_area(int l, int w, int h) {
  int return_value = 0;

  if (w <= 0 || l <= 0 || h <= 0)
    return_value = -1;
  else
    return_value = 2 * ((w * l) + (l * h) + ( w * h));
  
  return return_value;
}

/*jacobsthal performs operations on two numbers to result in the next term.*/
long jacobsthal(short n) {
  long prev_1 = 1;
  long prev_2 = 0;
  long return_value = 0;  
  int i = 0;
    
  if (n < 0)
     return_value = -1;

  /* if n is 0 or 1, the return value should be n.*/
  else if (n == prev_1 || n == prev_2)
     return_value = n;

  else
   {
     for (i = 0; i < n - 1; i++)
      { 
         return_value = (2 * prev_2) + prev_1;
	 /*updates the previous two numbers.*/
	 prev_2 = prev_1; 
         prev_1 = return_value;
      }
    }

    return return_value;
}

short ith_digit(long n, unsigned short i) {

  long duplicate = n; 
  int exponent = 0; 
  int count = 1;
  int return_value = 0;

  /*converts duplicate to a positive number if n is negative */
  if (duplicate < 0)
    {
      duplicate = -n;
      n = -n;
    }
    
  /*calculates the number of digits n has*/
  while (duplicate > 9) 
   {
     duplicate /= 10; 
     count++; 
   }    
   
  /*incorrect cases return -1.*/
  if (i > count || i == 0) 
     return_value = -1; 

  else  
   {  
     for (exponent = 0; exponent < (i - 1); exponent++) 
       n /= 10; 

     for (exponent = 0; exponent < (count - i); exponent++) 
       n %= 10; 
     
     return_value = n; 
    }
  
  return return_value;
}
