#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int pid = fork();
    if(pid>0)
    {
          printf("Parent process id %d\n", getpid());
          printf("Child process id %d\n", pid);
    }
    else
    {
        if(pid == 0)
        {
              sleep(10);
              printf("Child process id %d\n", getpid());
              printf("Parent process id %d\n", getppid());
        }
    }
  return 0;
}
