#include "sh.h"

/**
 * It parses a command, and if it sees a pipe, it parses another command and returns a pipe command
 * 
 * @param ps pointer to the start of the string
 * @param es end of string
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return cmd;
}
