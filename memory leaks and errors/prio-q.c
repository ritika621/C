/* Name : Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID: 117272918
   Discussion Section: 0107

I pledge on my honor that I have not given or received any 
unauthorized assistance on this assignment

This file performs operations on a priority queue. It intitializes
the priority queue, inserts elements into the enqueue, calculates 
its size, checks to see if it is empty, returns the string data
of its last element, returns the string data of its last element
and removes it from the queue. It also returns an array of all
the strings in the priority queue. In addition, it frees dynamically
allocated data in an array of strings and clears a queue by freeing
all its elements and data. This file also returns the priority of
an element given its string data and removes elements between a given
range in the queue by freeing memory associated to those elements.
Finally, it changes the priority of an element of the queue, given 
its string data.
*/

#include "prio-q.h"
#include <stdlib.h>
#include <string.h>

/* This function initializes the priority queue by making the head 
and tail  point to NULL to represent an empty queue.*/

void init(Prio_que *const prio_q)
{ if(prio_q != NULL)
    { prio_q -> head = NULL;
  prio_q -> tail = NULL;
}
}

/*This function inserts an element into the priority queue and sets
  its data to be identical to the string new_element[]. It also
sets the priority of the element as the parameter priority.*/

unsigned int enqueue(Prio_que *const prio_q, const char new_element[]
, unsigned int priority)
{ 
  Node *curr = NULL;
  Node *new_node = NULL;

  /*returns 0 if the priority is negative.*/
  if (priority < 0 || prio_q == NULL || new_element == NULL)
    return 0;
 
  /*checks if the queue is empty or not*/
  if (prio_q -> head != NULL && prio_q -> tail != NULL)
    curr = prio_q -> head;

  /*moves the curr pointer until it reaches a posiiton
    where its priority is in ascending order with thw
    queue.*/

  while ( curr != NULL && curr -> priority <= priority)
    {
      /*checks for duplicate priorities.*/
      if (curr ->  priority == priority)
	return 0;
      curr = curr -> next;
    }

  /*allocates memory for the pointers new_node
    and data. assigns the required priority
    to the new node.*/

  new_node = malloc(sizeof(*new_node));
  new_node -> data = malloc(strlen(new_element)+ 1);
  new_node -> priority = priority;
    
  /*copies the new_element[] string to
    the data string of the new node.*/
  strcpy(new_node -> data, new_element);

  /*checks if this is the first element
    of the queue to insert. Therefore,
  the head and tail of the queue
  will point to the new node.*/
  if (prio_q -> head == NULL)
    {
      prio_q -> head = new_node;
      prio_q -> tail = new_node;
      new_node -> next = NULL;
      new_node -> prev = NULL;
    }

  /* checks if the new node has the smallest
     priority in the queue and needs to be the
     first element in the queue.Therefore,
     the head of the queue will point to the
     new node.*/
  else if (curr == prio_q -> head)
    {
      new_node -> prev = NULL;
      new_node -> next = prio_q -> head;
      curr -> prev = new_node;
      prio_q -> head = new_node;
    }

  /* checks if the new node has the priority 
     and needs to be added to the back of the list.
     Therefore, the tail of the queue will point to 
     the new node.*/
   else if (curr == NULL)
     {
       new_node -> prev = prio_q -> tail;
       (prio_q -> tail) -> next = new_node;
       new_node -> next = curr;
       prio_q -> tail = new_node;
     }

  /*If the new node needs to be added
    to the middle of the queue it updates
    the next and previous accordingly.*/
   else
     {
       new_node -> prev = curr -> prev;
       new_node -> next = curr;
       curr -> prev -> next = new_node;
       curr -> prev = new_node;
     }
  return 1;
}

/*This function returns the size of the priority
  queue by finding the number of nodes it contains.*/
unsigned int size(const Prio_que prio_q)
{
  int size = 0;
  Node *curr;

  /*If the queue is empty, it returns 0.*/
  if (prio_q.head == NULL)
    return 0;
  
  /*starts counting the nodes
    from the head of the queue*/
  curr = prio_q.head;
  
  /*moves the position of the current
pointer until it reaches the end of the queue
while keeping track of the number of times
the pointer has moved as the size of the queue.*/
  while (curr != NULL)
    {
      curr = curr -> next;
      size++;
    }

  return size;
}

/*This functions checks if the queue is empty.
It returns 1 if it is empty and 0 if it is not
empty*/
unsigned int is_empty (const Prio_que prio_q)
{
  /*if the list is empty, the head of the queue
    will not point to anything.*/
 if ((prio_q.head) == NULL)
    return 1;
  else
    return 0;
}

/*This function returns a string identical to the
 string data of the element with the highest priority
 in the queue. This would be the last element in the
queue.*/

char *peek(Prio_que prio_q)
{
  char *element = NULL;

  /*If the queue is empty, it returns NULL.*/
  if (prio_q.head == NULL)
    return NULL;

  /*allocates memory for the string 'element'
    based on the size of the string data of the node.*/
  element = malloc(strlen((prio_q.tail) -> data)+1);
  /*copys the string data to the string element.*/
  strcpy(element,(prio_q.tail) -> data);

  return element;
}

/*This function removes the element with the 
highest priority in the queue and returns its 
string data. The highest priority element is the
last element of the queue.*/
char *dequeue(Prio_que *const prio_q)
{
  char *element;

  /*checks if the pointer is NULL or if the queue
    is empty.*/
  if (prio_q == NULL || prio_q -> head == NULL)
    return NULL;

  /*element points to the string data of the element
    with the highest priority*/
  element = (prio_q -> tail) -> data;
  /*If there is more than one element in the queue
    it updates the tail of the queue to the second
last eement in the queue and makes its 'next' as NULL
to indicate the end of the queue.*/

  if (prio_q -> tail != prio_q -> head)
    {

      prio_q -> tail = (prio_q -> tail) -> prev;
      prio_q -> tail -> next -> prev = NULL;
      free(prio_q -> tail -> next);
    (prio_q -> tail) -> next = NULL;
    }

  /*If there is only one element in the queue, it
    makes the queue empty*/
  else
    {
      prio_q -> head = NULL;
      free(prio_q -> tail);

      prio_q -> tail = NULL;
    }

  return element; 
}

/*This functions returns an array of strings that are copies of
  the elements stored in the queue. In addition, they are 
stored in the array in decreasing order of their priority
and the last element of the array is NULL.*/
char **get_all_elements(Prio_que prio_q)
{
  char **all_elements;
  int i = 0;
  int count = 0;
  Node *curr;

  /*allocates memory to the array of strings with size as
    the size of the queue plus 1 for the last element NULL*/
  all_elements = malloc(sizeof(char *) * (size(prio_q) + 1));
   
  /*checks if the queue isn't empty*/
  if (prio_q.head != NULL)
    {
      /*begins by pointing curr to the end of the queue as
	the last element of the queue has the highest priority.*/
      curr = prio_q.tail;

      /*allocates memory for every element of the array
based on the size of the string data for the current node
and copies the string data's contents into the element of the array.
moves the current node pointer to the left with each iteration.*/
      for (i = size(prio_q) - 1; i >= 0; i--)
	{
	  all_elements[count] = malloc(strlen(curr -> data) + 1);
	  strcpy(all_elements[count], curr -> data);
	  if (i != 0)
	    curr = curr -> prev;
	  count++;
	}
    }

  /*assigns the last element of the array to be NULL.*/
  all_elements[size(prio_q)] = NULL;

  return all_elements;
}

/*This function frees all the dynamically-allocated memory of the
 strings in the array name_list and frees the array name_list itself.
 It has no effect if name_list is NULL.*/
void free_name_list(char *name_list[])
{
  int i = 0;

  if (name_list != NULL)
    {
      /*frees all the strings in name_list*/
      while (name_list[i] != NULL)
	{
	  free(name_list[i]);
	  name_list[i] = NULL;
	  i++;
	}
      /*frees the array itself*/
      free(name_list);
      name_list = NULL;
    }
}

/*This function delallocates all dynamically-allocated memory that 
prio_q points to, and therefore destroying the queue and all its data
.*/
void clear (Prio_que *const prio_q)
{
  Node *curr;
 
  if (prio_q != NULL && prio_q -> head != NULL)
    {
      curr = prio_q -> head -> next;
      prio_q -> head = NULL;
      
      /*frees all the data and memory of the priority queue up until
	the tail*/
      while (curr != NULL)
       {
	  free (curr -> prev -> data);
	  curr -> prev -> data = NULL;
	  curr -> prev -> next = NULL;
	  free(curr -> prev);
	  curr -> prev = NULL;
	  curr = curr -> next;
       }
       
      /*frees all the data and memory of the tail of the queue*/
      free(prio_q -> tail -> data);
      prio_q -> tail -> data = NULL;
      free(prio_q -> tail);
      prio_q -> tail = NULL;
    }
 }

/*This function searches for the element of the queue with the same
data as element[] and returns its priority if it has one. If element
is found more than once, it returns the highest priority element
is stored with. If element[] isn't present at all then it returns -1.
*/
int get_priority(Prio_que prio_q, char element[])
{
  int returnPriority = -1;
  Node *curr;
  
  if (element != NULL)
    {
      curr = prio_q.head;
  
      /*iterates through the queue until it finds element[] and 
	reassigns returnPriority to its priority. If more than one 
	element has data as element[], returnPriority will be 
	replaced with the highest priority.*/
      while (curr != NULL)
	{
	  if (strcmp(curr -> data, element) == 0)
	  returnPriority = curr -> priority;
	  curr = curr -> next;
	}
    }
  return returnPriority;
}

/*This function removes all elements from prio_q with priority 
greater than or equal to low and less than or equal to high. If no 
elements are removed it returns 0 and doesnt change anything. 
Otheriwse it removes the elements and returns the number of elements 
removed. It also properly frees all memory being used to store
all elements being removed.*/
unsigned int remove_elements_between(Prio_que *const prio_q,
		    unsigned int low, unsigned int high)
{
  Node *curr;
  Node *low_node;
  int count = 0;
  int i = 0;

  if (prio_q != NULL)
    {
      curr = prio_q -> head;
      low_node = prio_q -> head;

      /*accounts for no elements to be removed*/
      if ((prio_q -> tail -> priority) > (low - 1))
	{
	  /*checks if curr is in the range of low and high.*/
	  while (curr != NULL  && curr -> priority < (high + 1))
	    {
	      curr = curr -> next;
	      
	      /*Keeps moving low_node until it reaches the first
		element	with priority greater than low*/
	      if (i == 0 && ((low_node -> priority) < low))
		{
		  low_node = low_node -> next;
		}

	      /*When low_node reaches the fist element with priority
greater than low, it moves low_node one element back to ensure
that low_node points to the element after which elements until high
will be removed. It increments i so that the element low_node points
to doesn't change.*/
	      else if (i == 0)
		{
		  low_node = low_node -> prev;
		  i++;
		}
            
	      /*After the required low_node has been reached, it 
frees data associated to successive elements after low_node until
curr reaches a priority greater than high.*/
	      if (i != 0)
		{
		  free(curr -> prev -> data);
		  curr -> prev -> data = NULL;
		  curr -> prev -> prev = NULL;
		  curr -> prev -> next = NULL;
		  free(curr -> prev);
		  curr -> prev = NULL;
		  i++;
		  count++;
		}
	      
	      /*If the tail of the queue is to be removed, it does 
		this separately since we can't free the previous
		of something that is NULL.*/
	      if (curr -> next == NULL && curr -> priority < (high + 
							     1))
		{ 
                  free(curr -> data);
		  curr -> data = NULL;
		  curr -> prev = NULL;
		  curr -> next = NULL;
		  free(curr);
		  curr = NULL;
		  i++;
		  count++;
		}
            }
	}
	  /*checks if at least one element was removed.*/
	  if (curr != prio_q -> head)
	    {
	      /*checks if all elements were removed.*/
	      if (curr == NULL && low_node == NULL)
		{
		  prio_q -> tail = NULL;
		  prio_q -> head = NULL;
		}
	      
	      /*checks if the head was removed and updates the head*/
	      else if (low_node == NULL)
		{
		  prio_q -> head = curr;
		  prio_q -> head -> prev = NULL;
		}
	      
	      /*checks if the tail was removed and updates the tail*/
	      else if (curr == NULL)
		{
		  prio_q -> tail = low_node;
		  prio_q -> tail -> next = NULL;
		}
	      
	      /*for all other normal cases*/ 
	      else
		{
		  low_node -> next = curr;
		  curr -> prev = low_node;
		}
	    }
	}
  return count;
}

/*changes the priority of the elemnt element[] to new_priority and
returns 1 if this is successful. It returns 0 and has no effect if
element is not present, if new_priority already exists in the 
queue, or if there are multiple occurences of element[] with 
different priorities.*/ 
unsigned int change_priority(Prio_que *prio_q, char element[], 
unsigned int new_priority)
{
  int return_value = 0;
  Node *curr;
  Node *node = NULL;

  if (prio_q != NULL)
    {
      curr = prio_q -> head;

      while (curr != NULL && curr-> priority != new_priority)
	{
	  if( strcmp(element, curr -> data) == 0)
	    {
	      /*return_value keeps track of the number of times 
		element[] is in the queue and node keeps track
		of the element with data as element[].*/
	      return_value++;
	      node = curr;
	    }   

	  curr = curr -> next;
	}
    }

  /*if element[] only occurs once, its priority is changed.*/
  if (return_value == 1)
    { 
      node -> priority = new_priority;
      return 1;
    }
  else
    return 0;
}

