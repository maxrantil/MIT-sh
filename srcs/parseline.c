#include "sh.h"

/**
 * It parses a line of input,
 * which is a sequence of commands separated by semicolons, and returns a command
 * tree representing the line
 * 
 * @param ps pointer to the start of the string
 * @param es end of string
 * 
 * @return A pointer to a command structure.
 */
t_cmd	*parseline(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parsepipe(ps, es);
	while (peek(ps, es, "&"))
	{
		gettoken(ps, es, 0, 0);
		cmd = backcmd(cmd);
	}
	if (peek(ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return cmd;
}
