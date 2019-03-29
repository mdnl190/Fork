#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void printChars(int n, char c)
{
	for (int i = 0; i < n; i++)
	{
		putchar(c);
		fflush(stdout);
	}
}

int getNum (int argC, char* argv[])
{
	int result = 10000;
	if (argC >= 2) result = atoi(argv[1]);
	return result;
}

void forking(int num, pid_t p, char c1, char c2)
{
	int status;
	switch(p){
			case -1: 
				perror("fork() error");
				break;
			case 0:
				printChars(num/2, c1);
				fflush(stdout);
				break;
			default:
				wait(&status);
				printChars(num/2, c2);
				fflush(stdout);
				break;
		}
}

int main(int argC, char* argv[], char* envp[])
{	
	int num = getNum(argC,argv);
	pid_t top = getpid();	

	pid_t p1, p2;

	
	p1 = fork();
	p2 = fork();

	forking(num, p1, 'A', 'B');
	forking(num, p2, 'C', 'D');

	if (getpid() == top) printf("\n");
	return 0;
}
