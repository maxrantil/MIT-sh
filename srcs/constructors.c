#include "sh.h"

/**
 * It allocates memory for a new t_execcmd structure, sets all the fields to 0, and sets the type field
 * to EXEC
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	execcmd(void)
{
	t_execcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (t_cmd*)cmd;
}

/**
 * It takes a command, a file, an error file, a mode, and a file descriptor, and returns a redirection
 * command
 * 
 * @param subcmd the command to redirect
 * @param file The file to redirect to.
 * @param efile the file to redirect stderr to.
 * @param mode 0 for <, 1 for >, 2 for >>, 3 for <>, 4 for <<
 * @param fd the file descriptor to redirect.
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_redircmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return (t_cmd*)cmd;
}

/**
 * It takes two commands and returns a pipe command
 * 
 * @param left The left side of the pipe.
 * @param right The right side of the pipe.
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (t_cmd*)cmd;
}

/**
 * It takes two commands and returns a command that executes the first command, then the second command
 * 
 * @param left The left side of the list.
 * @param right The right side of the list.
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	listcmd(t_cmd *left, t_cmd *right)
{
	t_listcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return (t_cmd*)cmd;
}

/**
 * It takes a command and returns a command that runs the command in the background
 * 
 * @param subcmd The command to run in the background.
 * 
 * @return A pointer to a t_cmd struct.
 */
t_cmd*	backcmd(t_cmd *subcmd)
{
	t_backcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return (t_cmd*)cmd;
}