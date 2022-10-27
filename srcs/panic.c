#include "sh.h"

/**
 * It prints the string s to the standard error output and then exits the program
 * 
 * @param s the string to print
 */
void	panic(char *s)
{
	dprintf(2, "%s\n", s);
	exit(1);
}
