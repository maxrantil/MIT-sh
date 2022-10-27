#include "sh.h"

/**
 * Fork1() is a wrapper for fork() that panics if the fork fails
 * 
 * @return The pid of the child process.
 */
int	fork1(void)
{
	int pid;

	pid = fork();
	if(pid == -1)
		panic("fork");
	return pid;
}
