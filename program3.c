/* Write a program using fork to create a child process.
   a) The parent process should sort numbers in ascending order and child process should sort numbers in descending order
   b) Orphan Process
   c) Zombie process
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void print_array(int arr[], int size)
{
	for(int i=0; i<size; i++) printf("%d ", arr[i]);
	printf("\n");
}

void sort_ascending(int arr[], int size)
{
	for(int i=0; i<size-1; i++)
	{
		for(int j=i+1; j<size; j++)
		{
			if(arr[i] > arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void sort_descending(int arr[], int size)
{
	for(int i=0; i<size-1; i++)
	{
		for(int j=i+1; j<size; j++)
		{
			if(arr[i] < arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main()
{
	int size;
	printf("Enter size of array : ");
	scanf("%d", &size);

	int arr[size];
	printf("Start to enter the elements with space : ");
	for(int i=0; i<size; i++) scanf("%d", &arr[i]);

	pid_t num_pid = fork();
	if(num_pid < 0)
	{
		printf("Error in fork execution\n");
		exit(1);
	}
	else if(num_pid == 0)
	{
		printf("This is the child process id %d\n", getpid());
		printf("This is the child process pp id %d\n", getppid());
		sort_ascending(arr, size);
		printf("Sorted ascending array in child: ");
		print_array(arr, size);
	}
	else 
	{
		printf("This is the parent id %d\n", getpid());
		printf("This is the parent pp id %d\n", getppid());
		wait(NULL);
		sort_descending(arr, size);
		printf("Sorted descending array in parent: ");
		print_array(arr, size);
	}
	return 0;
}
	
	

