
#include "../incl/minishell.h"

void	piping(int fd[2], int fd_in)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd_in != -1)
		close(fd_in);
}

static void	mutli_error(t_tok *token, t_env *envlst)
{
	if (token->cmd[0] && path_is_dir(token->path))
	{
		path_error(token->path, 3);
		exit_free(token, envlst, 0);
		exit(g_sig[1]);
	}
	if (token->error)
	{
		gestion_error(token, envlst);
		exit_free(token, envlst, 0);
		exit(g_sig[1]);
	}
}

void	exec_or_error(t_tok *token, t_env *envlst)
{
	char		**env;

	mutli_error(token, envlst);
	if (token->cmd[0] && !token->error && builtins(token->cmd[0]))
	{
		manage_bultins(token, envlst, 2);
	}
	else if (!token->error && token->cmd[0])
	{
		env = env_lst_to_tab(envlst);
		execve(token->path, token->cmd, env);
		free_tab(env);
		print_msg(2, "bash: ", token->cmd[0], ": Permission denied\n");
		exit_free(token, envlst, 0);
		exit(126);
	}
	exit_free(token, envlst, 0);
	exit(0);
}

int	exec(t_tok *token, t_env *envlst, int fd[2], int fd_in)
{
	int			pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		reset_signals_2();
		if (fd[0] == -1 || fd[1] == -1)
		{
			gestion_error(token, envlst);
			exit_free(token, envlst, 0);
			exit(g_sig[1]);
		}
		piping(fd, fd_in);
		exec_or_error(token, envlst);
		exit(0);
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	return (pid);
}
