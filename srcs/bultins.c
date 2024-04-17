
#include "../incl/minishell.h"

int	manage_bultins(t_tok *token, t_env *envlst, int mode)
{
	if (solo_token_bultins(token, envlst, mode))
		return (1);
	if (!ft_strcmp(token->cmd[0], "echo"))
	{
		if (mode)
			my_echo(token);
		return (1);
	}	
	if (!ft_strcmp(token->cmd[0], "env"))
	{
		if (mode)
			my_env(token, envlst);
		return (1);
	}
	if (!ft_strcmp(token->cmd[0], "pwd"))
	{
		if (mode)
			my_pwd();
		return (1);
	}
	return (0);
}

int	solo_token_bultins(t_tok *token, t_env *envlst, int mode)
{
	if (!ft_strcmp(token->cmd[0], "unset"))
	{
		if (mode == 2)
			my_unset(token, envlst);
		return (1);
	}
	if (!ft_strcmp(token->cmd[0], "cd"))
	{
		if (mode == 2)
			my_cd(token, envlst);
		return (1);
	}
	if (!ft_strcmp(token->cmd[0], "export"))
	{
		if (mode == 2 || (mode && !token->cmd[1]))
			my_export(token, envlst);
		return (1);
	}
	if (!ft_strcmp(token->cmd[0], "exit"))
	{
		if (mode)
			my_exit(token, envlst, mode);
		return (1);
	}
	return (0);
}
