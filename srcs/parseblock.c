#include "sh.h"

/**
 * It parses a block of commands, which is a parenthesized list of commands
 * 
 * @param ps pointer to the start of the string
 * @param es end of string
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	parseblock(char **ps, char *es)
{
	t_cmd *cmd;

	if (!peek(ps, es, "("))
		panic("parseblock");
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		panic("syntax - missing )");
	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}
