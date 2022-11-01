// Shell.
#include "sh.h"

/**
 * It reads a line from the user and stores it in the buffer pointed to by buf
 * 
 * @param buf the buffer to store the command in
 * @param nbuf The size of the buffer.
 * 
 * @return The return value is the number of bytes read.
 */
static int	getcmd(char *buf, int nbuf)
{
	dprintf(2, "$ ");
	memset(buf, 0, nbuf);
	gets(buf);
	if(buf[0] == 0) // EOF
		return -1;
	return 0;
}

/**
 * It reads a line from the console, forks a child process, and then runs the command in the child
 * process
 */
int	main(void)
{
	static char buf[100];
	int fd;

	// Ensure that three file descriptors are open.
	while ((fd = open("console", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}

	// Read and run input commands.
	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			// Chdir must be called by the parent, not the child.
			buf[strlen(buf) - 1] = 0;  // chop \n
			if (chdir(buf + 3) < 0)
				dprintf(2, "cannot cd %s\n", buf + 3);
			continue;
		}
		if (fork1() == 0)
			runcmd(parsecmd(buf));
		wait(0);
	}
	exit(0);
}
