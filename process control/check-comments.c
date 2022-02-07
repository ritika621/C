#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <sysexits.h>
#include "safe-fork.h"

int main(int argc, char **argv)
{
  pid_t child_x, child_y;
  int pipefd[2];
  int count_x = 0;
  int count_y = 0;

  if(argc < 2)
    exit(2);

  pipe(pipefd);
  child_x = safe_fork();
  if (child_x > 0)
    {
      dup2(pipefd[0], STDIN_FILENO);
      scanf("%d", &count_x);
      child_y = safe_fork();
      if(child_y > 0)
	{
	  scanf("%d", &count_y);
	  if(count_y >= (2 * count_x))
	    {
	      printf("Enough comments!\n");
	      exit(0);
	    }
	  else
	    {
	      printf("Too few comments!\n");
	    exit(1);
	    }

	}
      else
	{
	  dup2(pipefd[1], STDOUT_FILENO);
	  execl("/bin/wc", "wc", "-m", argv[1], NULL);
	}
    }

      else 
	{
	  dup2(pipefd[1], STDOUT_FILENO);
	  execlp("./remove-comments.x", "remove-comments.x", argv[1], NULL);
	}
  return 0;
}
