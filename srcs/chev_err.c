
#include "../incl/minishell.h"

void	messg_err(char c, int fl)
{
	if (fl)
	{
		ft_putstr_fd("bash: syntax error near unexpected ", 2);
		ft_putstr_fd("token `newline'\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
}

int	err_found(int j, char *str)
{
	if (!str[j])
	{
		messg_err(str[j], 1);
		return (1);
	}
	if (str[j] == '<' || str[j] == '>' || str[j] == '|')
	{
		messg_err(str[j], 0);
		return (1);
	}
	return (0);
}

int	chev_err(char *str)
{
	int		i;
	int		j;
	char	*quote;

	i = 0;
	quote = quote_secur(str);
	while (str[i])
	{
		j = i;
		if (quote[j] == '0' && (str[j] == '>' || str[j] == '<'))
		{
			if (str[j + 1] && (str[j + 1] == '>' || str[j + 1] == '<'))
				j += 1;
			if (str[j + 1])
				j++;
			while (str[j] && (str[j] == ' ' || str[j] == '\t'))
				j++;
			if (err_found(j, str))
				return (1);
		}
		i++;
	}
	return (0);
}
