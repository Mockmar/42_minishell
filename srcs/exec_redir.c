
#include "../incl/minishell.h"

int	redir_input(int fdin, t_tok *token)
{
	if (fdin == -1)
		return (-1);
	if (token->fd_input == -2)
		fdin = dup(token->fd_hdoc);
	else if (token->fd_input)
		fdin = dup(token->fd_input);
	if (fdin == -1)
		return (-1);
	return (fdin);
}

int	redir_output(int fdout, t_tok *token)
{
	int			last_fd;

	if (fdout == -1)
		return (-1);
	last_fd = 0;
	if (token->file_output)
	{
		dup2(token->fd_output, fdout);
		last_fd = token->fd_output;
	}
	if (last_fd == -1)
	{
		close(fdout);
		return (-1);
	}
	return (fdout);
}
