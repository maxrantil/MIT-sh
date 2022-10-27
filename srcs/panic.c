#include "sh.h"

void	panic(char *s)
{
	dprintf(2, "%s\n", s);
	exit(1);
}

