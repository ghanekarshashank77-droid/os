#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void forkexample()
{
    int x =1;
    if(fork() == 0)
      printf("Child has x = %d\n" , ++x);
    else
      printf("Parent has x = %d\n" , --x);
}
    
int main()
{
	// fork();
	// printf("Hi!\n");
	// fork();
	// printf("Hello!\n");
	
	// fork();
	// fork();
	// fork();
	// printf("Hello\n");
	
	forkexample();
	
	return 0;
}
