
#include "../incl/minishell.h"

int	beg_or_end_pipe(char *str)
{
	int		i;
	char	*quote;

	i = 0;
	quote = quote_secur(str);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '|' && quote[i] == '0')
	{
		print_msg(2, "bash: syntax error near", NULL, NULL);
		print_msg(2, " unexpected token `|'\n", NULL, NULL);
		return (1);
	}
	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && str[i] == '|' && quote[i] == '0')
	{
		print_msg(2, "bash: syntax error near", NULL, NULL);
		print_msg(2, " unexpected token `|'\n", NULL, NULL);
		return (1);
	}
	return (0);
}

int	two_pipe(char *str)
{
	int		i;
	int		j;
	char	*quote;

	i = 0;
	quote = quote_secur(str);
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '|' && quote[i] == '0')
		{
			while (str[j] == '\n' || str[j] == '\t' || str[j] == ' '
				|| str[j] == '\b' || str[j] == '\v')
				j++;
			if (str[j] == '|')
			{
				print_msg(2, "bash: syntax error near", NULL, NULL);
				print_msg(2, " unexpected token `|'\n", NULL, NULL);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	only_ws(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	unclose_quote(char *str)
{
	char	*quote;

	quote = quote_secur(str);
	if (quote[ft_strlen(str) - 1] != '0')
	{
		print_msg(2, "bash: ", "syntax error unclosed quote\n", NULL);
		free(quote);
		return (1);
	}
	free(quote);
	return (0);
}

int	syntax_check(char *str)
{
	if (beg_or_end_pipe(str) || two_pipe(str) || unclose_quote(str)
		|| chev_err(str))
	{
		g_sig[1] = 2;
		return (1);
	}
	if (only_ws(str))
		return (1);
	return (0);
}
