
#include "../incl/minishell.h"

int	my_pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(NULL, 0);
	if (!str)
	{
		ft_putstr_fd("pwd: getcwd error\n", 2);
		g_sig[1] = 1;
		return (0);
	}
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	free(str);
	g_sig[1] = 0;
	return (0);
}

char	*ft_getenv(t_env *envlst, char *name)
{
	char	*value;

	value = NULL;
	while (envlst)
	{
		if (!ft_strcmp(name, envlst->name))
			value = ft_strdup(envlst->value);
		envlst = envlst->next;
	}
	return (value);
}
