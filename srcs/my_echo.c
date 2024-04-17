
#include "../incl/minishell.h"

static int	echo_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

int	my_echo(t_tok *token)
{
	int	i;
	int	newline_option;

	i = 1;
	newline_option = false;
	if (token->cmd[1])
		newline_option = echo_newline(token->cmd[1]);
	if (newline_option)
		i++;
	while (token->cmd[i] && echo_newline(token->cmd[i]))
		i++;
	while (token->cmd[i])
	{
		ft_putstr_fd(token->cmd[i], 1);
		i++;
		if (token->cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (!newline_option)
		ft_putstr_fd("\n", 1);
	g_sig[1] = 0;
	return (0);
}
