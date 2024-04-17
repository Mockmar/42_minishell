
#include "../incl/minishell.h"

char	*quote_secur(char *str)
{
	int		i;
	char	*secu;
	char	flag;

	i = -1;
	flag = 0;
	secu = ft_calloc(sizeof(char *), ft_strlen(str) + 1);
	if (!secu)
		return (NULL);
	while (str[++i])
	{
		if (!flag)
			secu[i] = '0';
		if (flag == '\"')
			secu[i] = '1';
		if (flag == '\'')
			secu[i] = '2';
		if (flag && (str[i] == flag || str[i] == flag))
			flag = 0;
		else if (!flag && (str[i] == '"' || str[i] == '\''))
			flag = str[i];
		if (!flag)
			secu[i] = '0';
	}
	return (secu);
}

char	*suppr_quote(char *str)
{
	char	*ret;
	char	*quote;
	int		i;

	i = 0;
	ret = NULL;
	quote = quote_secur(str);
	while (str[i])
	{
		if (!((str[i] != '\"' || str[i] != '\'') && quote[i] == '0'))
			ret = ft_straddchar(ret, str[i]);
		i++;
	}
	if (!ret)
	{
		ret = malloc(sizeof(char *));
		if (!ret)
			return (NULL);
		ret[0] = 0;
	}
	free(quote);
	free(str);
	return (ret);
}
