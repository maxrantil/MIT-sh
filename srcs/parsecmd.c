#include "sh.h"

/**
 * It parses a command line,
 * and returns a pointer to a structure that represents the command line
 * 
 * @param s the string to parse
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd	*parsecmd(char *s)
{
	char *es;
	t_cmd *cmd;

	es = s + strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		dprintf(2, "leftovers: %s\n", s);
		panic("syntax");
	}
	nulterminate(cmd);
	return cmd;
}
