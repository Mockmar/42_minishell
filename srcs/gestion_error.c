
#include "../incl/minishell.h"

int	error_heredoc(t_tok *token)
{
	if (token->error == 11)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(token->file_output, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_sig[1] = 1;
		return (1);
	}
	while (token)
	{
		if (token->fd_hdoc == -1)
			return (1);
		token = token->next;
	}
	return (0);
}

int	gestion_error(t_tok *token, t_env *envlst)
{
	if (error_heredoc(token))
		return (1);
	if (path_error_2(token))
		return (1);
	if (manage_bultins(token, envlst, 0))
		return (0);
	if (path_error(token->cmd[0], token->error))
		return (1);
	if (path_is_dir(token->path))
		return (path_error(token->cmd[0], 3));
	return (0);
}

int	path_is_dir(char *str)
{
	struct stat	buf;

	if (stat(str, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}

int	path_error(char *str, int error)
{
	if (error == 1)
	{
		print_msg(2, "bash: ", str, ": No such file or directory\n");
		g_sig[1] = 127;
		return (1);
	}
	if (error == 2)
	{
		print_msg(2, str, ": command not found\n", NULL);
		g_sig[1] = 127;
		return (1);
	}
	if (error == 3)
	{
		print_msg(2, "bash: ", str, ": Is a directory\n");
		g_sig[1] = 126;
		return (1);
	}
	if (error == 4)
	{
		print_msg(2, "bash: ", str, ": Permission denied\n");
		g_sig[1] = 126;
		return (1);
	}
	return (0);
}

int	path_error_2(t_tok *tok)
{
	if (tok->error == 12)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(tok->f_input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_sig[1] = 1;
		return (1);
	}
	if (tok->error == 13)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(tok->f_input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_sig[1] = 1;
		return (1);
	}
	if (tok->error == 14)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(tok->file_output, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_sig[1] = 1;
		return (1);
	}
	return (0);
}
