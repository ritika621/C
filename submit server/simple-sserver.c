/* Name : Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID: 117272918
   Discussion Section: 0107

I pledge on my honor that I have not given or received any
unauthorized assistance on this assignment

This file stores a list of compile commands read from a file and a list of test
commands read from a file in a struct of type Commands. Therefore, this struct
contains 2 linked list, one for the compile commands and one for the test 
commands. It also contains a function to free all the dynammically allocated
memory in a specific Commands struct using a helper function to generalize
freeing up the memory. In addition, this file executes the 
compilation commands and testing commands through child processes and accounts
for input and output redirection. For simplicity and efficiency, there are 2 
helper functions. Since the compilation commands and test commands need to be
stored the same way, just in separate lists, there is a function called 
store_program() to generalize this. In addition, the compilation and test 
commands need to be executed in similar ways except for the return value. For
this, there is a function called exec_program() to generalize this and avoid
redundant code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple-sserver.h"
#include "split.h"
#include <fcntl.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <err.h> 
#include <sysexits.h>
#include "safe-fork.h"
#include <sys/wait.h>

/*Helper function prototypes*/

static void store_commands(Commands *const cmds, int compile_or_test,
 FILE *file_read);
static int exec_program(Commands *const commands, int compile_or_test);

/*This function reads compilation and test commands from 2 separate files and
stores them in 2 separate linked lists in a Commands structure. If the files to
read from don't exist, the function exits wtih status 1. This function uses
the helper function store_commands() to store the commands into the 2 linked 
lists.
*/

Commands read_commands(const char compile_cmnds[], const char test_cmnds[])
{
  FILE *file_compile;
  FILE *file_test; 
  Commands cmds;
  
  /*checks if the parameters are NULL.*/
  if (compile_cmnds == NULL || test_cmnds == NULL)
    exit(1);

  /*stores the fie descriptors for the compile file and test file.*/
  file_compile = fopen(compile_cmnds,"r");
  file_test = fopen(test_cmnds, "r");
  
  /* checks if the file doesn't exist or if there is an error opening the file 
     for reading*/
  if (file_compile == NULL || file_test == NULL)
    exit(1);
 
  /*initializes the head and tail of both lists*/
  cmds.head_compile = NULL;
  cmds.tail_compile = NULL;
  cmds.tail_test = NULL;
  cmds.head_test = NULL;
 
  /*calls the helper function on both files(compilation commands and test 
    commands) to store them in their respective lists.*/
  store_commands(&cmds, 0, file_compile);
  store_commands(&cmds, 1, file_test);
 
  return cmds;
}

/*This helper function takes in a pointer to a Commands struct and a pointer 
to the file to be read from. The compile_or_test parameter is used to determine
whether we wish to store the commands in the compilation commands linked list
 or the test commands linked list. It then reads each line of the file using 
fgets() and stores the command in a node of the linked list.
*/ 
static void store_commands(Commands *const cmds, int compile_or_test, 
FILE *file_read)
{
   char array_commands[255];
   Node *head;
   Node *tail;
   Node *new_node;
   Node *curr;
   int count = 0;
 
   /*checks when the file has been fully read*/
   while (fgets(array_commands, 255, file_read) != NULL)
     {
       /*allocates memory for a new node*/
       new_node = malloc(sizeof(*new_node));
       
       /*For the first element in the list.*/
       if (count == 0)
	 {/*assigns the head of the list*/
	   head = new_node;
	   curr = head;
	 }   

       /*allocates memory for the string data to be stored in the element of
	 list and copies the command read from array_commands[] to the data of
	 the node */
       new_node -> data = malloc(strlen(array_commands) + 1);
       strcpy(new_node -> data, array_commands);
 
       /*if the new node is the first element it simply makes the prev and
next NULL. If the new node is not the first element, it links curr and 
new_node by making their next and prev point to each other repsectively.*/
       if (new_node == head)
	 {
	   new_node -> prev = NULL;
	   new_node -> next = NULL;
	 }
       else
	 {
	   new_node -> prev = curr;
	   new_node -> next = NULL;
	   curr -> next = new_node;
	   curr = curr -> next;
	 }
       count++;
     }

   /*assigns the tail of the list to the last node created*/
   tail = new_node;

   /*updates the head and tail of either the compilation commands list or the 
     testing commands list depending on the parameter compile_or_test*/
   if (compile_or_test == 0)
    {
      cmds -> head_compile = head;
      cmds -> tail_compile= tail;
    }
   else
     {
       cmds -> head_test = head;
       cmds -> tail_test = tail;
     } 

   /*closes the file after reading*/
   fclose(file_read);
 }

/*Given a Commands struct, this function executes the compilation commands in 
its compilation commands linked list. It uses the helper function exec_program()
to execute these commands and returns SUCCESSFUL_COMPILATION if it was compiled
successfuly and FAILED_COMPILATION if the compilation failed.*/

int compile_program(Commands commands)
{
  return exec_program(&commands, 0);
}

/*Given a Commands struct, this function executes the testing commands in its
testing commands linked list. It uses the helper function exec_program() to 
execute these commands and returns the number of tests that executed 
successfully.*/
int test_program(Commands commands)
{
  return exec_program(&commands, 1);
}

/*This function takes in a pointer to a Commands struct and uses the parameter
compile_or_test to determine whether the compilation commands or test commands
need to be executed for the function call. In both cases, it creates a child
process to execute each command and uses the split() function for input/output
redirection and to call execvp() for the program name when using PATH. If
it is called to execute compilation commands, it returns FAILED_COMPILATION
if there is any error in the child processes and doesn't execute any further
command. Otherwise it executes all commands and returns SUCCESSFUL_COMPILATION.
If it is called to execute test commands, it returns ignores errors in the 
child processes and returns the number of successful executions.
*/

static int exec_program(Commands *const commands, int compile_or_test)
{
  int i = 0;
  Node *curr;
  int count = 0;
  pid_t child;
  int file_d = 0;
  int status;
  char **words;
  int array_length = 0;
  Node *head;

  /* checks whether it should start from the head of the compilation commands 
     linked list or the test commands linked lists*/
  if (compile_or_test == 0)
    head = commands -> head_compile;
  else
    head = commands -> head_test;
  
  /*makes sure the list of commands isn't empty*/
  if (head != NULL)
    {
      curr = head;
      
      /*while loop ends when curr reaches the end of the list*/
      while (curr != NULL)
	{/*words stores every word of the command as an element of an array of 
	   string*/
	  words = split(curr -> data);
	  
	  /*array_length calculates how manys strings are stores in words.*/
	  while (words[i] != NULL)
	    {
	      array_length++;
	      i++;
	    }

	  /*creates a child process for every command*/
	  child = safe_fork();
	 
	  /*In the parent process, it waits for the exit status of the child 
process and if there is an error in a compilation command, it returns
FAILED_COMPILATION. If there is no error in a test command, it increments the 
number of successful executions of test commands.*/
	  if (child > 0)
	    {
	      wait(&status);
     
	      if (WIFEXITED(status))
		{
		  if(compile_or_test == 0 && WEXITSTATUS(status) != 0)
		    return FAILED_COMPILATION;
		  else if (compile_or_test !=0 && WEXITSTATUS(status) == 0)
		    count++;
		}
	    }

	  /*In the child process, it performs input/output redirection if it is
	    needed and executes the command*/
	  else      
	    {
	      /*checks for input/output redirection only if there are more than
		2 words in the command*/
	      if (array_length > 2)
		{
		  /*checks if input redirection is needed. If it is, it 
		    redirects the input, removes the last 2 strings from the 
		    array words by freeing them and updates the length of the
		    array words after removing the last 2 strings.*/
		  if (strcmp(words[array_length -2], "<") == 0)
		    {
		      file_d = open(words[array_length - 1], O_RDONLY);
		      dup2(file_d, STDIN_FILENO);
		      free(words[array_length-1]);
		      words[array_length-1] = NULL;
		      free(words[array_length -2]);
		      words[array_length - 2] = NULL;
		      array_length -= 2;
		    }
		  
		  /*checks if output redirection is needed. If it is, it 
		    redirects the output, removes the last 2 strings from the
		    array words by freeing them, and updates the length of the 
		    array words after removing the last 2 strings from it*/
		  else if (strcmp(words[array_length - 2], ">") == 0)
		    {
		      file_d = open(words[array_length - 1], FILE_FLAGS);
		      dup2(file_d, STDOUT_FILENO);
		      free(words[array_length - 1]);
		      words[array_length - 1] = NULL;
		      free(words[array_length - 2]);
		      words[array_length - 2] = NULL;
		      array_length -= 2;
	     
		      /*checks if input needs to be redirected along with the 
			above output redirection. If it does, it redirects the
			input, removes the last 2 strings from the array words
			and updates the length of the array words.*/
    
		      if(strcmp(words[array_length -2], "<") == 0)
			{
			  file_d = open(words[array_length - 1], O_RDONLY);
			  dup2(file_d, STDOUT_FILENO);
			  free(words[array_length - 1]);
			  words[array_length - 1] = NULL;
			  free(words[array_length - 2]);
			  words[array_length - 2] = NULL;
			  array_length -= 2;
			}
		    }
		}
	      /*executes the command*/
	      execvp(words[0], words);

	    }	 
	  /*updates curr to the next node in the list*/
	  curr = curr -> next;
	  i = 0;
      
	  /*frees up the memory from the array of strings called **words.*/
	  while(words[i] != NULL)
	    {
	      free(words[i]);
	      words[i] = NULL;
	      i++;
	    }

	  free(words);
	  words = NULL;
	}
    }

  /*returns the count for the testing commands and SUCCESSFUL_COMPILATION for
    the compilation commands*/  
  if(compile_or_test)
    return count;
  else 
    return SUCCESSFUL_COMPILATION;
}

/*This fucbntions frees all dynamically allocated memory associated with
the given pointer to a Commands struct. It uses a helper function to do
this since the dynamically allocated memory from the compilation
commands list and the test commands list need to be freed 
in the same way.*/ 
 void clear_commands(Commands *const commands)
 {
   Node *curr;

   if (commands != NULL)
     {  
       curr = commands -> head_compile;
  /*frees memory be incrementing the position of head
    in the list and freeing up the node previous to it*/
  while (curr != NULL)
    {
      commands -> head_compile  = curr -> next;
      free(curr -> data);
      curr -> data = NULL;
      curr -> prev = NULL;
      curr -> next = NULL;
      free(curr);
      if (commands -> head_compile != NULL) 
	commands -> head_compile -> prev = NULL;
      curr = commands -> head_compile;
    }
  commands -> tail_compile = NULL;
  curr = commands -> head_test;
  while(curr != NULL)
    {
      commands -> head_test = curr -> next;
      free(curr -> data);
      curr -> data = NULL;
      curr -> prev = NULL;
      curr -> next = NULL;
      free(curr);
      if(commands -> head_test != NULL)
	commands -> head_test -> prev = NULL;
      curr = commands -> head_test;
}
  commands -> tail_test = NULL;
     }
      
 } 

