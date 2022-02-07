/* Name : Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID: 117272918
   Discussion Section: 0107

I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment.*/
                                                                               
/*This file performs operations on a priority queue. It intitializes
the priority queue, inserts elements into the enqueue, calculates 
its size, checks to see if it is empty, returns the string data
of its last element, returns the string data of its last element
and removes it from the queue. It also returns an array of all
the strings in the priority queue.
*/

#include "prio-q.h"
#include <stdlib.h>
#include <string.h>

/* This function initializes the priority queue by making the head 
and tail  point to NULL to represent an empty queue.*/

void init(Prio_que *const prio_q)
{
  prio_q -> head = NULL;
  prio_q -> tail = NULL;
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
  char *element;

  /*If the queue is empty, it returns NULL.*/
  if (prio_q.head == NULL)
    return NULL;

  /*allocates memory for the string 'element'
    based on the size of the string data of the node.*/
  element = malloc(sizeof((prio_q.tail) -> data));
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
      (prio_q -> tail) -> next = NULL;
    }

  /*If there is only one element in the queue, it
    makes the queue empty*/
  else
    {
      prio_q -> head = NULL;
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



      
