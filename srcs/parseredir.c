#include "sh.h"

t_cmd*	parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			panic("missing file for redirection");
		switch (tok)
		{
			case '<':
				cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
				break;

			case '>':
				cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
				break;

			case '+':  // >>
				cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT, 1); //O_APPEND here??
				break;
		}
	}
	return cmd;
}