
#include "../incl/minishell.h"

static int	clean_exit(t_tok *token, t_env *envlst)
{
	int	ret;

	ret = 0;
	if (token->cmd[1])
		ret = ft_atoi(token->cmd[1]) % 256;
	free_token(token, NULL);
	free_env(envlst);
	if (ret < 0)
		ret = 256 + ret;
	printf("exit\n");
	return (ret);
}

static bool	is_valid(char *nbr)
{
	int	sign;

	sign = (nbr[0] == '-' || nbr[0] == '+');
	if ((19 + sign) < ft_strlen(nbr))
		return (false);
	if (nbr[0] != '-' && ft_strcmp(nbr + sign, "9223372036854775808") >= 0)
		return (false);
	if (nbr[0] == '-' && ft_strcmp(nbr + 1, "9223372036854775808") > 0)
		return (false);
	return (true);
}

static int	str_is_num(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (is_valid(str));
}

int	my_exit(t_tok *token, t_env *envlst, int mode)
{
	if (token->cmd[1] && !str_is_num(token->cmd[1]))
	{
		if (mode == 2)
			write(2, "exit\n", 6);
		print_msg(2, "bash: exit: ", token->cmd[1], NULL);
		write(2, ": numeric argument required\n", 29);
		free_token(token, NULL);
		free_env(envlst);
		exit(2);
	}
	else if (len_tab(token->cmd) > 2)
	{
		if (mode == 2)
			write(2, "exit\n", 6);
		print_msg(2, "bash: exit: too many arguments\n", NULL, NULL);
		g_sig[1] = 1;
		return (1);
	}
	if (mode == 2)
		exit(clean_exit(token, envlst));
	return (1);
}
