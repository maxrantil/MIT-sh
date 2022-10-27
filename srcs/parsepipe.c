#include "sh.h"

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
