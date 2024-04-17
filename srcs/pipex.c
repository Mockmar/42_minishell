
#include "../incl/minishell.h"

int	builtins(char *str)
{
	if (!str)
		return (-1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else
		return (0);
}

int	handle_redirects(int fd_rw[2], int fd_pipe[2], int next, t_tok *token)
{
	fd_rw[0] = redir_input(fd_pipe[0], token);
	if (next)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		fd_rw[1] = redir_output(fd_pipe[1], token);
	}
	else
		fd_rw[1] = redir_output(dup(STDOUT_FILENO), token);
	return (0);
}

int	forks(t_tok *token, t_env *envlst, int fd_rw[2], int fd_pipe[2])
{
	int			last_pid;

	last_pid = 0;
	while (token)
	{
		handle_redirects(fd_rw, fd_pipe, token->next != NULL, token);
		g_sig[1] = 0;
		last_pid = exec(token, envlst, fd_rw, fd_pipe[0]);
		token = token->next;
	}
	return (last_pid);
}

int	pipex(t_tok *token, t_env *envlst)
{
	int			last_pid;
	int			fd_pipe[2];
	int			fd_rw[2];

	last_pid = 0;
	fd_pipe[0] = dup(STDIN_FILENO);
	fd_pipe[1] = -1;
	if (token->cmd[0] && token->next == NULL && builtins(token->cmd[0]))
	{
		handle_redirects(fd_rw, fd_pipe, token->next != NULL, token);
		piping(fd_rw, fd_pipe[0]);
		g_sig[1] = 0;
		if (token->error)
			gestion_error(token, envlst);
		else
			manage_bultins(token, envlst, 2);
	}
	else
	{
		last_pid = forks(token, envlst, fd_rw, fd_pipe);
	}
	return (last_pid);
}
