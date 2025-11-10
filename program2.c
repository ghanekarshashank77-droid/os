#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

pid_t num_pid;
void main()
{
    num_pid = fork();
    if(num_pid < 0)
    {
      printf("Error in fork execution");
    }
    else
    {
      if(num_pid == 0)
      {
          printf("This is the child process id %d\n" , getpid());
          printf("This is the child process pp id %d\n" , getppid());
      }
      else
      {
          printf("This is the parent id %d\n" , getpid());
          printf("This is the parent pp id %d\n" , getppid());
          wait(NULL);
      }
    }
    exit(0);
} 
