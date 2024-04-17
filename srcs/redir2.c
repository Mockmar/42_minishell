
#include "../incl/minishell.h"

int	skipped_ws(char *content, int i)
{
	int	j;

	j = 1;
	if (!content[i + j])
		return (0);
	while (content[i + j] == ' ' || content[i + j] == '>'
		|| content[i + j] == '<')
		j++;
	return (j);
}

int	redir_out_2(t_tok *tok, int i)
{
	if (access(tok->file_output, F_OK) == 0)
	{
		if (access(tok->file_output, W_OK) != 0)
		{
			tok->error = 11;
			tok->fd_output = -3;
			return (i + 1);
		}
		if (tok->content[i + 1] == '>')
		{
			tok->fd_output = open(tok->file_output, O_APPEND | O_WRONLY);
			i++;
		}
		else
			tok->fd_output = open(tok->file_output, O_WRONLY | O_TRUNC);
	}
	else
	{
		if (tok->content[i + 1] == '>')
			i++;
		tok->fd_output = open(tok->file_output, O_CREAT | O_WRONLY, 0666);
		if (tok->fd_output == -1)
			tok->error = 14;
	}
	return (i);
}

int	redir_out(t_tok *tok, int i)
{
	if (tok->file_output != NULL)
	{
		free(tok->file_output);
		tok->file_output = NULL;
	}
	if (tok->fd_output != 1)
		close(tok->fd_output);
	tok->file_output = file_name(tok, i, tok->file_output);
	i = redir_out_2(tok, i);
	if (tok->fd_output == -1 && tok->error != 14)
		tok->error = 11;
	return (i);
}

int	clear_content_1(char *content, int i, char *quote)
{
	int	j;

	if ((content[i] == '<' || content[i] == '>')
		&& quote[i] == '0')
	{
		if (content[i + 1] == content[i])
			i++;
		j = skipped_ws(content, i);
		while ((content[i + j] && content[i + j] != ' ')
			|| (quote[i + j] && quote[i + j] != '0'))
			j++;
		i = i + j;
	}
	return (i);
}

char	*clear_content(char *content, char *quote, t_tok *tok)
{
	int		i;
	char	*cl;

	i = 0;
	cl = NULL;
	while (content[i])
	{
		i = clear_content_1(content, i, quote);
		if (content[i])
		{
			cl = ft_straddchar(cl, content[i]);
			if (!cl)
			{
				tok->error = 632;
				return (NULL);
			}
			i++;
		}
	}
	free(tok->content);
	tok->content = NULL;
	if (!cl)
		return (ft_calloc(sizeof(char *), 1));
	return (cl);
}
