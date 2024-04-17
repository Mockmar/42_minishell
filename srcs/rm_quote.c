
#include "../incl/minishell.h"

char	*file_name(t_tok *tok, int i, char *str)
{
	int	j;

	j = skipped_ws(tok->content, i);
	if (tok->content[i + j] == '\'' || tok->content[i + j] == '\"')
		j++;
	while ((tok->content[i + j] && tok->content[i + j] != ' '
			&& tok->content[i + j] != '<' && tok->content[i + j] != '>')
		|| (tok->quote[i + j] && tok->quote[i + j] != '0'))
	{
		if (!((tok->content[i + j] == '\'' || tok->content[i + j] == '\"')
				&& tok->quote[i + j] == '0'))
			str = ft_straddchar(str, tok->content[i + j]);
		j++;
	}
	return (str);
}

void	rm_pair(t_tok *tok, int i, char quote_t)
{
	int		dec;
	int		j;
	char	*ret;

	j = 0;
	dec = 0;
	ret = malloc(sizeof(char) * ft_strlen(tok->content));
	if (!ret)
		return ;
	while (j < (ft_strlen(tok->content) - 2))
	{
		if (j >= i && dec < 2 && (tok->content[j + dec] == quote_t))
			dec++;
		ret[j] = tok->content[j + dec];
		j++;
	}
	ret[j] = '\0';
	free(tok->content);
	tok->content = ret;
}

void	rm_quotes(t_tok *tok)
{
	int	i;
	int	j;

	i = 0;
	while (tok->content[i])
	{
		if ((tok->content[i] == '<' || tok->content[i] == '>')
			&& tok->quote[i] == '0')
		{
			j = skipped_ws(tok->content, i);
			if (tok->content[i + j] == '\"' || tok->content[i + j] == '\'')
				rm_pair(tok, i + j, tok->content[i + j]);
		}
		i++;
	}
}
