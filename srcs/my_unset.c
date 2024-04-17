
#include "../incl/minishell.h"

static void	unset2(t_env *env_ite, t_env *envlst)
{
	t_env	*env_tmp;

	free(env_ite->name);
	free(env_ite->value);
	if (!env_ite->next)
	{
		free(envlst);
		envlst = NULL;
	}
	else
	{
		env_ite->name = ft_strdup(env_ite->next->name);
		env_ite->value = ft_strdup(env_ite->next->value);
		env_tmp = env_ite->next->next;
		free(env_ite->next->name);
		free(env_ite->next->value);
		free(env_ite->next);
		env_ite->next = env_tmp;
	}
}

static void	unset3(t_env *env_ite)
{
	t_env	*env_tmp;

	env_tmp = env_ite->next->next;
	free(env_ite->next->name);
	free(env_ite->next->value);
	free(env_ite->next);
	env_ite->next = env_tmp;
}

int	my_unset(t_tok *token, t_env *envlst)
{
	int		i;
	t_env	*env_ite;
	int		len;

	i = 1;
	while (token->cmd[i])
	{
		env_ite = envlst;
		if (!ft_strcmp(env_ite->name, token->cmd[i])
			&& ft_strncmp("_", token->cmd[i], 2))
			unset2(env_ite, envlst);
		while (env_ite)
		{
			len = ft_strlen(token->cmd[i]) + 1;
			if (env_ite->next
				&& !ft_strncmp(env_ite->next->name, token->cmd[i], len)
				&& ft_strncmp("_", token->cmd[i], 2))
				unset3(env_ite);
			env_ite = env_ite->next;
		}
		i++;
	}
	return (0);
}
