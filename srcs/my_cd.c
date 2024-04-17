
#include "../incl/minishell.h"

int	change_pwd(t_env *envlst, char *path, char *new_path)
{
	while (envlst)
	{
		if (!ft_strncmp(envlst->name, "PWD", ft_strlen("PWD")))
		{
			free(envlst->value);
			envlst->value = NULL;
			envlst->value = new_path;
		}
		if (!ft_strncmp(envlst->name, "OLDPWD", ft_strlen("OLDPWD")))
		{
			if (path)
			{
				free(envlst->value);
				envlst->value = NULL;
				envlst->value = path;
			}
		}
		envlst = envlst->next;
	}
	return (1);
}

int	fail_cd(char *path)
{
	if (access(path, F_OK) != 0)
		print_msg(2, "bash: cd: ", path, ": No such file or directory\n");
	else
		print_msg(2, "bash: cd: ", path, ": Not a directory\n");
	g_sig[1] = 1;
	return (1);
}

int	my_cd_2(t_tok *token, t_env *envlst, char *path)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (!new_path && token->cmd[1][0] && !(token->cmd[1][0] == '/'))
	{
		g_sig[1] = 1;
		return (print_msg(2, "cd: getcwd error\n", NULL, NULL));
	}
	change_pwd(envlst, path, new_path);
	return (0);
}

int	my_cd(t_tok *token, t_env *envlst)
{
	char	*path;

	g_sig[1] = 0;
	if (!token->cmd[1] || token->cmd[2])
	{
		write(2, "cd: error argument\n", ft_strlen("cd: error argument\n"));
		g_sig[1] = 1;
		return (1);
	}
	path = getcwd(NULL, 0);
	if (!path && token->cmd[1][0] && !(token->cmd[1][0] == '/'))
	{
		g_sig[1] = 1;
		return (print_msg(2, "cd: getcwd error\n", NULL, NULL));
	}
	if (chdir(token->cmd[1]) == 0)
		return (my_cd_2(token, envlst, path));
	else
		return (fail_cd(token->cmd[1]));
}
