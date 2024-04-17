
#include "../incl/minishell.h"

static int	replace_in_envlst2(t_env *envlst, char *new_name, char *new_value)
{
	free(envlst->name);
	envlst->name = NULL;
	envlst->name = ft_strdup(new_name);
	if (envlst->value)
	{
		free(envlst->value);
		envlst->value = NULL;
		envlst->value = ft_strdup(new_value);
	}
	else
		envlst->value = ft_strdup(new_value);
	return (1);
}

int	replace_in_envlst(t_env *envlst, char *new_name, char *new_value)
{
	while (envlst)
	{
		if (!ft_strncmp(new_name, envlst->name, ft_strlen(envlst->name) + 1))
			return (replace_in_envlst2(envlst, new_name, new_value));
		if (envlst->next)
			envlst = envlst->next;
		else
			break ;
	}
	if (env_lstadd_back(&envlst, env_lstnew(ft_strdup(new_name))))
		return (0);
	envlst = envlst->next;
	envlst->value = ft_strdup(new_value);
	return (1);
}

int	export_as_env(t_env *envlst)
{
	while (envlst)
	{
		printf("export %s=%s\n", envlst->name, envlst->value);
		envlst = envlst->next;
	}
	return (1);
}

static void	my_export2(t_env *envlst, t_tok *token, char *str, int i)
{
	char	*new_value;
	char	*new_name;
	int		len_name;

	new_name = NULL;
	new_value = NULL;
	len_name = ft_strlen(token->cmd[i]) - ft_strlen(str);
	new_name = malloc(sizeof(*new_name) * (len_name + 1));
	if (!new_name)
		return ;
	ft_strlcpy(new_name, token->cmd[i], len_name + 1);
	str++;
	if (!str)
	{
		new_value = malloc(sizeof(char *));
		if (!new_value)
			return ;
		new_value[0] = 0;
	}
	else
		new_value = ft_strdup(str);
	replace_in_envlst(envlst, new_name, new_value);
	free(new_name);
	free(new_value);
}

int	my_export(t_tok *token, t_env *envlst)
{
	char	*str;
	int		i;

	i = 1;
	if (!token->cmd[1] && export_as_env(envlst))
		return (1);
	while (token->cmd[i])
	{
		if (!valid_identifier(token->cmd[i]))
			return (0);
		str = ft_strchr(token->cmd[i], '=');
		if (str)
			my_export2(envlst, token, str, i);
		i++;
	}
	return (1);
}
