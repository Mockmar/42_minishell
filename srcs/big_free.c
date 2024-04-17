
#include "../incl/minishell.h"

int	free_env(t_env *envlst)
{
	t_env	*env_tmp;

	while (envlst)
	{
		if (envlst->name)
			free(envlst->name);
		if (envlst->value)
			free(envlst->value);
		env_tmp = envlst;
		envlst = envlst->next;
		free(env_tmp);
		env_tmp = NULL;
	}
	return (1);
}

static void	free_tokenbis(t_tok *token)
{
	if (token->content)
		free(token->content);
	if (token->limiter)
		free(token->limiter);
	if (token->quote)
		free(token->quote);
	if (token->cmd)
		free_tab(token->cmd);
	if (token->f_input)
		free(token->f_input);
	if (token->file_output)
		free(token->file_output);
	if (token->path)
		free(token->path);
	if (token->multi_path)
		free_tab(token->multi_path);
}

t_tok	*free_token(t_tok *token, t_tok *ret)
{
	t_tok	*free_token;

	while (token)
	{
		free_tokenbis(token);
		if (token->fd_output != 1)
			close(token->fd_output);
		if (token->fd_input != 0 && token->fd_input != -2)
			close(token->fd_input);
		free_token = token;
		token = token->next;
		free(free_token);
	}
	return (ret);
}

void	free_one_token(t_tok *token)
{
	free_tokenbis(token);
	if (token->fd_output != 1)
		close(token->fd_output);
	if (token->fd_input != 0 && token->fd_input != -2)
		close(token->fd_input);
	free(token);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
