
#include "../incl/minishell.h"

char	*recup_name(char *env_line)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (env_line[i] && env_line[i] != '=')
	{
		name = ft_straddchar(name, env_line[i]);
		if (!name)
			return (NULL);
		i++;
	}
	return (name);
}

t_env	*error_env(void)
{
	char	*path;
	t_env	*envlist;

	envlist = NULL;
	path = getcwd(NULL, 0);
	if (!path)
		return (print_msg(2, "cd: getcwd error\n", NULL, NULL), NULL);
	if (env_lstadd_back(&envlist, env_lstnew(ft_strdup("PWD"))))
		return (NULL);
	envlist->value = path;
	if (env_lstadd_back(&envlist, env_lstnew(ft_strdup("_"))))
		return (NULL);
	envlist->next->value = ft_strdup("/usr/bin/env");
	return (envlist);
}

t_env	*lst_env(char **env)
{
	int		i;
	t_env	*envlist;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		if (env_lstadd_back(&envlist, env_lstnew(recup_name(env[i]))))
			return (NULL);
		i++;
	}
	return (envlist);
}

int	set_value(t_env *envlist)
{
	while (envlist)
	{
		envlist->value = ft_strdup(getenv(envlist->name));
		if (!envlist->value)
		{
			envlist->value = malloc(sizeof(char *));
			if (!envlist->value)
				return (0);
			envlist->value[0] = 0;
		}
		envlist = envlist->next;
	}
	return (0);
}

char	**env_lst_to_tab(t_env *envlist)
{
	char	**env;
	char	*tmp;
	int		lenlst;
	int		i;

	i = 0;
	lenlst = env_lstsize(envlist);
	env = malloc(sizeof(*env) * (lenlst + 1));
	if (!env)
		return (NULL);
	while (envlist)
	{
		tmp = NULL;
		tmp = ft_strjoin(envlist->name, "=");
		env[i] = ft_strjoin(tmp, envlist->value);
		free(tmp);
		i++;
		envlist = envlist->next;
	}
	env[i] = NULL;
	return (env);
}
