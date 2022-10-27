#include "sh.h"

/**
 * It parses a command,
 * which is either a parenthesized block, or a sequence of tokens separated by
 * redirection operators, and terminated by a pipe, semicolon, or ampersand
 * 
 * @param ps pointer to the start of the command string
 * @param es end of string
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	parseexec(char **ps, char *es)
{
	char		*q;
	char		*eq;
	int			tok;
	int			argc;
	t_execcmd	*cmd;
	t_cmd 		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));

	ret = execcmd();
	cmd = (t_execcmd*)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|)&;"))
	{
		if ((tok = gettoken(ps, es, &q, &eq)) == 0)
			break;
		if (tok != 'a')
			panic("syntax");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return ret;
}
