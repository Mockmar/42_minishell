
#include "../incl/minishell.h"

int	redir_in_2(t_tok *tok, int i)
{
	if (tok->content[i])
		i++;
	if (tok->limiter)
	{
		free(tok->limiter);
		tok->limiter = NULL;
	}
	tok->limiter = file_name(tok, i, tok->limiter);
	if (tok->heredoc)
	{
		free(tok->heredoc);
		tok->heredoc = NULL;
	}
	tok->fd_hdoc = heredoc(tok->limiter);
	g_sig[0] = 0;
	tok->fd_input = -2;
	return (i);
}

int	redir_in_3(t_tok *tok, int i)
{
	tok->f_input = file_name(tok, i, tok->f_input);
	if (access(tok->f_input, F_OK) != 0)
	{
		tok->error = 13;
		return (i);
	}
	tok->fd_input = open(tok->f_input, O_RDONLY);
	if (tok->fd_input == -1)
	{
		tok->fd_input = -3;
		tok->error = 12;
	}
	return (i);
}

int	redir_in(t_tok *tok, int i)
{
	if (tok->f_input != NULL)
	{
		free(tok->f_input);
		tok->f_input = NULL;
	}
	if (tok->fd_input != 0 && tok->fd_input != -2)
		close(tok->fd_input);
	if (tok->content[i + 1] && tok->content[i + 1] == '<')
		return (redir_in_2(tok, i));
	else
		return (redir_in_3(tok, i));
}

void	redir(t_tok *tok)
{
	int	i;

	i = 0;
	tok->quote = quote_secur(tok->content);
	while (tok->content[i])
	{
		if (tok->content[i] == '>' && tok->quote[i] == '0')
			i = redir_out(tok, i);
		if (tok->content[i] == '<' && tok->quote[i] == '0')
			i = redir_in(tok, i);
		if (tok->error != 0)
		{
			tok->content = clear_content(tok->content, tok->quote, tok);
			return ;
		}
		i++;
	}
	tok->content = clear_content(tok->content, tok->quote, tok);
}
