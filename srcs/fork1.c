#include "sh.h"

int	fork1(void)
{
	int pid;

	pid = fork();
	if(pid == -1)
		panic("fork");
	return pid;
}
