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

Commands read_commands(const char compile_cmnds[], const char test_cmnds[]){
  FILE *file_compile;
  FILE *file_test;
  Node *new_node;
  Node *curr;
  Commands cmds;
  char read_commands[255];
  int count = 0;


  if(compile_cmnds == NULL || test_cmnds == NULL)
    exit(1);
  file_compile = fopen(compile_cmnds,"r");
  file_test = fopen(test_cmnds, "r");
  
  if(file_compile == NULL || file_test == NULL)
    exit(1);
 
  cmds.head_compile = NULL;
  cmds.tail_test = NULL;
  cmds.tail_compile = NULL;
 cmds.head_test = NULL;
 
 

 while(fgets(read_commands, 255, file_compile) != NULL){
 
     new_node = malloc(sizeof(*new_node));
     if(count == 0)
       {      cmds.head_compile = new_node;
	 curr = cmds.head_compile;}   
new_node -> data = malloc(strlen(read_commands) + 1);
   strcpy(new_node -> data, read_commands);
 if(new_node == cmds.head_compile)
   {new_node -> prev = NULL;
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
 
cmds.tail_compile = new_node;
  count = 0;

 while(fgets(read_commands, 255, file_test)!= NULL){
   
   new_node = malloc(sizeof(*new_node));
   if(count == 0)
     {  cmds.head_test = new_node;   
       curr = cmds.head_test;}
new_node -> data = malloc(strlen(read_commands) + 1);
   strcpy(new_node -> data, read_commands);
 if(new_node == cmds.head_test)
   {new_node -> prev = NULL;
     new_node -> next = NULL;
   }
     
 else
   {new_node -> prev = curr;
     new_node -> next = NULL;
     curr -> next = new_node;
     curr = curr -> next;
   }
 count++;
}
cmds.tail_test = new_node;
 fclose(file_compile);
 fclose(file_test);
return cmds;
}

int compile_program(Commands commands)
		      {int i = 0;
  Node *curr;
  pid_t child;
  int file_d = 0;
  int status;
  char **words;
  int array_length = 0;
  if(commands.head_compile != NULL){
  curr = commands.head_compile;
  while (curr != NULL)
    {words = split(curr -> data);
      while(words[i] != NULL)
	{
	  array_length++;
	  i++;
	}
      child = safe_fork();
      if(child > 0)
	{	wait(&status);
     
	  if(WIFEXITED(status))
	{
	  if(WEXITSTATUS(status) != 0)
	    return FAILED_COMPILATION;
	}
	}
else      
  {if(array_length > 2){
	  if(strcmp(words[array_length -2], "<") ==0)
	    {file_d = open(words[array_length - 1], O_RDONLY);
	      dup2(file_d, STDIN_FILENO);
	      free(words[array_length-1]);
	      words[array_length-1] = NULL;
	      free(words[array_length -2]);
		     words[array_length - 2] = NULL;
		     array_length -= 2;
}
	  else if( strcmp(words[array_length - 2], ">") == 0)
	    {
	      file_d = open(words[array_length - 1], FILE_FLAGS);
	      dup2(file_d, STDOUT_FILENO);
	      free(words[array_length - 1]);
	      words[array_length - 1] = NULL;
	      free(words[array_length - 2]);
	      words[array_length - 2] = NULL;
	      array_length -= 2;
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
	    execvp(words[0], words);
	}	 

	    
      curr = curr -> next;
      i = 0;
      while(words[i] != NULL)
	{	free(words[i]);
      words[i] = NULL;
      i++;
    }
      free(words);
      
      words = NULL;
    }
  }
  return SUCCESSFUL_COMPILATION;
}
 
 void clear_commands(Commands *const commands)
 {Node *curr;

   if (commands != NULL)
     {
       curr = commands -> tail_compile -> prev;
       while(curr != NULL)
	 {
	   free(curr-> next -> data);
	   curr -> next -> data = NULL;
	   curr -> next -> prev = NULL;
	   free(curr -> next);
	     curr -> next = NULL;
	   curr = curr -> prev;
	 }
       free(commands -> head_compile -> data);
       commands -> head_compile -> data = NULL;
       commands -> head_compile -> next = NULL;
       free(commands -> head_compile);
       commands -> head_compile = NULL;
       commands -> tail_compile = NULL;

curr = commands -> tail_test -> prev;
       while(curr != NULL)
         {
           free(curr-> next -> data);
           curr -> next -> data = NULL;
           curr -> next -> prev = NULL;
           free(curr -> next);
             curr -> next = NULL;
           curr = curr -> prev;
         }
       free(commands -> head_test -> data);
       commands -> head_test -> data = NULL;
       commands -> head_test -> next = NULL;
       free(commands -> head_test);
       commands -> head_test= NULL;
       commands -> tail_test = NULL;
       
       
     }
 }
int test_program(Commands commands)
{int file_d = 0;
int i = 0;
  Node *curr;
  pid_t child;
  int status;
  char **words;
  int count= 0;
  int array_length = 0;
  if (commands.head_test != NULL){
  curr = commands.head_test;
  while (curr != NULL)
    {words = split(curr -> data);
      while(words[i] != NULL)
	{	array_length++;
      i++;
    }
      child = safe_fork();
      if(child > 0)
        {       wait(&status);

          if(WIFEXITED(status))
        {
          if(WEXITSTATUS(status) == 0)
            count++;
        }
        }
      else
	{if(array_length > 2){
if(strcmp(words[array_length -2], "<") ==0)
            {file_d = open(words[array_length - 1], O_RDONLY);
              dup2(file_d, STDIN_FILENO);
              free(words[array_length-1]);
              words[array_length-1] = NULL;
              free(words[array_length -2]);
                     words[array_length - 2] = NULL;
                     array_length -= 2;
}
          else if( strcmp(words[array_length - 2], ">") == 0)
            {
              file_d = open(words[array_length - 1], FILE_FLAGS);
              dup2(file_d, STDOUT_FILENO);
              free(words[array_length - 1]);
              words[array_length - 1] = NULL;
              free(words[array_length - 2]);
              words[array_length - 2] = NULL;
              array_length -= 2;
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
 execvp(words[0], words);

	}
      curr = curr -> next;
      i = 0;
      while(words[i] != NULL)
        {       free(words[i]);
      words[i] = NULL;
      i++;
    }
      free(words);
      words = NULL;
    }}
  
  return count;
}

