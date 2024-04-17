
#include "../incl/minishell.h"

int	path_cmd(t_tok *token)
{
	char	*str_desact;

	str_desact = quote_secur(token->cmd[0]);
	if (cmd_is_path(token->cmd[0], str_desact))
	{
		token->path = ft_strdup(token->cmd[0]);
		if (access(token->path, F_OK))
			token->error = 1;
	}
	else
	{
		token->path = find_path(token->multi_path, token->cmd[0]);
		if (!token->path)
			token->error = 2;
	}
	if (token->path && !token->error && access(token->path, X_OK))
			token->error = 4;
	free(str_desact);
	return (0);
}

int	cmd_is_path(char *str, char *quote)
{
	int	i;

	i = 0;
	while (str[i] && quote[i])
	{
		if (str[i] == '/' && quote[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

char	*find_path(char **multi_path, char *cmd)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin("/", cmd);
	while (multi_path && multi_path[i])
	{
		str = ft_strjoin(multi_path[i], tmp);
		if (access(str, F_OK) == 0)
		{
			free(tmp);
			return (str);
		}
		i++;
		free(str);
	}
	free(tmp);
	return (NULL);
}
