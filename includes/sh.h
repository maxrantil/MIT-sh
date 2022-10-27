#ifndef SH_H
# define SH_H

#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5

#define MAXARGS 10

typedef struct cmd {
	int type;
}	t_cmd;

typedef struct execcmd {
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
}	t_execcmd;

typedef struct redircmd {
	int type;
	struct cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
}	t_redircmd;

typedef struct pipecmd {
	int type;
	struct cmd *left;
	struct cmd *right;
}	t_pipecmd;

typedef struct listcmd {
	int type;
	struct cmd *left;
	struct cmd *right;
}	t_listcmd;

typedef struct backcmd {
	int type;
	struct cmd *cmd;
}	t_backcmd;

//Constructors
t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*listcmd(t_cmd *left, t_cmd *right);
t_cmd	*backcmd(t_cmd *subcmd);


int		fork1(void);
void	panic(char*);
t_cmd	*parsecmd(char*);
void	runcmd(t_cmd *cmd);
int		gettoken(char **ps, char *es, char **q, char **eq);
int		peek(char **ps, char *es, char *toks);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
t_cmd	*parseblock(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
t_cmd	*nulterminate(t_cmd *cmd);

#endif