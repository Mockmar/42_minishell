
#include "../incl/minishell.h"

void	redir_token(t_tok *token)
{
	while (token)
	{
		if (token->next)
		{
			token->next->fd_input = token->fd_output;
			token->next->f_input = ft_strdup(token->file_output);
		}
		token = token->next;
	}
}

t_tok	*parsing(char *str, t_env *envlst)
{
	char	*str_desact;
	t_tok	*token;

	str_desact = quote_secur(str);
	if (!str_desact)
		return (NULL);
	token = token_izer(str, str_desact);
	free(str_desact);
	init_token(token, envlst);
	if (!token_split_and_varenv(token, envlst))
		return (free_token(token, NULL));
	return (token);
}

int	token_split_and_varenv(t_tok *token, t_env *envlst)
{
	while (token)
	{
		if (envlst)
			token->content = import_varsenv(envlst, token->content, 0);
		if (token->content[0])
			redir(token);
		if (token->error == 632)
			return (0);
		token->cmd = ft_split_cmd(token->content);
		if (!token->cmd)
			return (0);
		trim_path_et_cmd(token);
		if (builtins(token->cmd[0]) == 0)
			path_cmd(token);
		token = token->next;
	}
	return (1);
}

void	trim_path_et_cmd(t_tok *token)
{
	char	**tab;

	if (token->cmd[0])
	{
		tab = trim_cmd(token->cmd);
		free_tab(token->cmd);
		token->cmd = tab;
	}
}
