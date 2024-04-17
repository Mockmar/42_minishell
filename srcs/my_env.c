
#include "../incl/minishell.h"

int	my_env(t_tok *token, t_env *envlst)
{
	char	**env;

	g_sig[1] = 0;
	if (token->cmd[1])
	{
		write(2, "env: invalide argument\n", 24);
		g_sig[1] = 1;
	}
	else if (envlst)
	{
		env = env_lst_to_tab(envlst);
		print_tab(env);
		free_tab(env);
	}
	return (0);
}
