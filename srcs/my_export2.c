
#include "../incl/minishell.h"

static void	print_indentifier(char *str, int mode)
{
	if (mode == 1)
	{
		print_msg(2, "bash: export: ", str, ": not a valid identifier\n");
	}
	if (mode == 2)
	{
		print_msg(2, "bash: export: ", str, ": not a valid identifier\n");
	}
	if (mode == 3)
	{
		print_msg(2, "bash: export: ", str, ": not a valid identifier\n");
	}
	g_sig[1] = 1;
}

int	valid_identifier(char *str)
{
	int	i;
	int	is_num;

	i = 0;
	is_num = 1;
	if (str[0] == '=')
		return (print_indentifier(str, 1), 0);
	if (ft_isdigit(str[i]))
		return (print_indentifier(str, 1), 0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (print_indentifier(str, 2), 0);
		if (!ft_isdigit(str[i]))
			is_num = 0;
		i++;
	}
	if (is_num)
		return (print_indentifier(str, 3), 0);
	return (1);
}
