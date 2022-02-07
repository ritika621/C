/* Name : Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID: 117272918
   Discussion Section: 0107

I pledge on my honor that I have not given or received any
unauthorized assistance on this assignment
*/

typedef struct node{
  char *data;
  struct node *next;
  struct node *prev;
} Node;

/*This Commands struct contains two linked lists. One for the compilation
  commands and one for the test commands.*/
typedef struct commands{
  Node *head_compile;
  Node *tail_compile;
  Node *head_test;
  Node *tail_test;
} Commands;
