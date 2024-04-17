
#include "../incl/minishell.h"

int	g_sig[2];

void	sigint( int code)
{
	(void)code;
	if (!g_sig[0])
		write(1, "\n", 1);
	else
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig[1] = 130;
}

int	main(int ac, char **av, char **env)
{
	t_env	*envlst;

	(void)av;
	(void)ac;
	g_sig[0] = 1;
	g_sig[1] = 0;
	signal(SIGINT, &sigint);
	signal(SIGQUIT, SIG_IGN);
	if (!env[0] || !env)
		envlst = error_env();
	else
	{
		envlst = lst_env(env);
		set_value(envlst);
	}
	launch_minish(envlst);
	return (0);
}
