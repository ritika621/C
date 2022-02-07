/* Name : Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID: 117272918
   Discussion Section: 0107

I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment.

This file containes 2 structures. One is for the priority queue which contains
head and tail pointers that both point to nodes. The other is for a node in the
queue which contains a string data, priority, and next and prev pointers
that point to nodes before and after the current node.*/

typedef struct node{
  char *data;
  int priority;
  struct node *next;
  struct node *prev;
} Node;

typedef struct prio_que{
  Node *head;
  Node *tail;
} Prio_que;
