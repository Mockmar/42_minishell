
#include "../incl/minishell.h"

t_tok	*token_izer(char *str, char *str_desac)
{
	t_tok		*lst_tok;
	char		*cmd_cut;
	int			i;

	i = 0;
	lst_tok = NULL;
	while (str[i])
	{
		cmd_cut = NULL;
		cmd_cut = cp_cmd(str, str_desac, &i);
		if (cmd_cut)
			if (tok_lstadd_back(&lst_tok, tok_lstnew(cmd_cut)))
				return (NULL);
		if (str[i])
			i++;
	}
	return (lst_tok);
}

char	*cp_cmd(char *str, char *quote, int *i)
{
	char	*cmd_cut;

	cmd_cut = NULL;
	while (str[*i] && quote[*i] == '0' && str[*i] == ' ')
		*i = *i + 1;
	while (str[*i] && (quote[*i] != '0' || str[*i] != '|'))
	{
		cmd_cut = ft_straddchar(cmd_cut, str[*i]);
		*i = *i + 1;
	}
	return (cmd_cut);
}
