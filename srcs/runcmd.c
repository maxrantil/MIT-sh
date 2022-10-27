#include "sh.h"

/**
 * It runs a command
 * 
 * @param cmd The command to run.
 */
// Execute cmd.  Never returns.
void	runcmd(t_cmd *cmd)
{
	int p[2];
	t_backcmd *bcmd;
	t_execcmd *ecmd;
	t_listcmd *lcmd;
	t_pipecmd *pcmd;
	t_redircmd *rcmd;

	if(cmd == 0)
		exit(1);

	switch(cmd->type)
	{
		default:
			panic("runcmd");

		case EXEC:
			ecmd = (t_execcmd*)cmd;
			if(ecmd->argv[0] == 0)
				exit(1);
			execvp(ecmd->argv[0], ecmd->argv);
			dprintf(2, "exec %s failed\n", ecmd->argv[0]);
			break;

		case REDIR:
			rcmd = (t_redircmd*)cmd;
			close(rcmd->fd);
			if(open(rcmd->file, rcmd->mode) < 0)
			{
				dprintf(2, "open %s failed\n", rcmd->file);
				exit(1);
			}
			runcmd(rcmd->cmd);
			break;

		case LIST:
			lcmd = (t_listcmd*)cmd;
			if(fork1() == 0)
				runcmd(lcmd->left);
			wait(0);
			runcmd(lcmd->right);
			break;

		case PIPE:
			pcmd = (t_pipecmd*)cmd;
			if (pipe(p) < 0)
				panic("pipe");
			if (fork1() == 0)
			{
				close(1);
				dup(p[1]);
				close(p[0]);
				close(p[1]);
				runcmd(pcmd->left);
			}
			if (fork1() == 0)
			{
				close(0);
				dup(p[0]);
				close(p[0]);
				close(p[1]);
				runcmd(pcmd->right);
			}
			close(p[0]);
			close(p[1]);
			wait(0);
			wait(0);
			break;

		case BACK:
			bcmd = (t_backcmd*)cmd;
			if(fork1() == 0)
				runcmd(bcmd->cmd);
			break;
	}
	exit(0);
}
