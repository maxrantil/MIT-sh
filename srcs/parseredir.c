#include "sh.h"

/**
 * It parses the redirection operators <, >, and >>, and returns a command structure with the
 * appropriate redirection information
 * 
 * @param cmd the command to redirect
 * @param ps pointer to the start of the command
 * @param es end of string
 * 
 * @return A pointer to a t_cmd struct.
 */
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