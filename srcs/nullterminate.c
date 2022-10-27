#include "sh.h"

// NUL-terminate all the counted strings.
t_cmd*	nulterminate(t_cmd *cmd)
{
	int i;
	t_backcmd	*bcmd;
	t_execcmd	*ecmd;
	t_listcmd	*lcmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if(cmd == 0)
		return 0;

	switch(cmd->type)
	{
		case EXEC:
			ecmd = (t_execcmd*)cmd;
			for(i=0; ecmd->argv[i]; i++)
			*ecmd->eargv[i] = 0;
			break;

		case REDIR:
			rcmd = (t_redircmd*)cmd;
			nulterminate(rcmd->cmd);
			*rcmd->efile = 0;
			break;

		case PIPE:
			pcmd = (t_pipecmd*)cmd;
			nulterminate(pcmd->left);
			nulterminate(pcmd->right);
			break;

		case LIST:
			lcmd = (t_listcmd*)cmd;
			nulterminate(lcmd->left);
			nulterminate(lcmd->right);
			break;

		case BACK:
			bcmd = (t_backcmd*)cmd;
			nulterminate(bcmd->cmd);
			break;
  	}
  	return cmd;
}
