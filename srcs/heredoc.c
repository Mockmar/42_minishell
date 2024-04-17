
#include "../incl/minishell.h"

static void	sighandler_heredoc(int signum)
{
	(void)signum;
	g_sig[1] = 130;
}

void	handle_signals_heredoc(void)
{
	signal(SIGINT, &sighandler_heredoc);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	heredochild(char *limiter, int *pipefd)
{
	char	*str;

	reset_signals();
	str = NULL;
	while (1)
	{
		str = readline("heredoc>");
		if (!str || !ft_strncmp(str, limiter, ft_strlen(limiter) + 1))
		{
			close(pipefd[1]);
			if (str)
				free(str);
			else
				printf("\n");
			free(limiter);
			exit(0);
		}
		close(pipefd[0]);
		write(pipefd[1], str, strlen(str));
		write(pipefd[1], "\n", 1);
		free(str);
	}
}

int	heredoc(char *limiter)
{
	pid_t	pid;
	int		pipefd[2];
	int		ret;

	ret = 0;
	if (pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
		heredochild(limiter, pipefd);
	handle_signals_heredoc();
	close(pipefd[1]);
	waitpid(pid, &ret, 0);
	signal(SIGINT, &sigint);
	if (ret)
	{
		write(1, "\n", 1);
		return (-1);
	}
	return (pipefd[0]);
}
