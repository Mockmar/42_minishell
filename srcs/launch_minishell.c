
#include "../incl/minishell.h"

void	exit_free(t_tok *token, t_env *envlst, int mode)
{
	free_token(token, NULL);
	free_env(envlst);
	if (mode == 1)
		printf("exit\n");
	if (mode)
		exit(g_sig[1]);
}

static int	launch_minish_2(t_tok *token, t_env *envlst, char *str)
{
	t_tok	*first_token;

	add_history(str);
	if (syntax_check(str) == 0)
	{
		token = parsing(str, envlst);
		if (!token)
			return (0);
		executing(token, envlst);
		first_token = token;
		free_token(first_token, NULL);
	}
	return (1);
}

int	launch_minish(t_env *envlst)
{
	t_tok	*token;
	char	*str;

	while (1)
	{
		token = NULL;
		g_sig[0] = 1;
		str = readline("minishell->");
		if (!str)
			exit_free(token, envlst, 1);
		g_sig[0] = 0;
		if (str[0])
			if (!launch_minish_2(token, envlst, str))
				return (0);
		free(str);
	}
	return (1);
}
