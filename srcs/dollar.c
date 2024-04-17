
#include "../incl/minishell.h"

static int	len_varsenv(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
	{
		if (i && str[i] == '$')
			break ;
		i++;
	}
	return (i);
}

static char	*concat_str(char *str, char *var_env, int i, int len)
{
	char	*str_tmp;
	char	*ret;
	char	*ret_bis;

	str_tmp = malloc(sizeof(char *) * (i + 1));
	if (!str_tmp)
		return (NULL);
	ft_strlcpy(str_tmp, str, i + 1);
	ret = ft_strjoin(str_tmp, var_env);
	free(str_tmp);
	free(var_env);
	str_tmp = malloc(sizeof(char *) * (ft_strlen(str) - (i + len) + 1));
	if (!str_tmp)
		return (NULL);
	ft_strlcpy(str_tmp, str + i + len, ft_strlen(str) - (i + len) + 1);
	ret_bis = ft_strjoin(ret, str_tmp);
	free(str_tmp);
	free(ret);
	return (ret_bis);
}

static char	*suppr_namevars(char *str, int i, int len)
{
	char	*str_tmp;
	char	*str_tmp2;
	char	*ret;

	str_tmp = malloc(sizeof(char *) * (i + 1));
	if (!str_tmp)
		return (NULL);
	ft_strlcpy(str_tmp, str, i + 1);
	str_tmp2 = malloc(sizeof(char *) * (ft_strlen(str) - (i + len) + 1));
	if (!str_tmp2)
		return (NULL);
	ft_strlcpy(str_tmp2, str + i + len, ft_strlen(str) - (i + len) + 1);
	ret = ft_strjoin(str_tmp, str_tmp2);
	free(str_tmp);
	free(str_tmp2);
	return (ret);
}

static char	*import_varsenvbis(char *str, int i, int len, char *var_env)
{
	char	*new_str;
	char	*str_tmp;

	if (!ft_strncmp("$?", str + i, 2))
	{
		str_tmp = ft_itoa(g_sig[1]);
		new_str = concat_str(str, str_tmp, i, 2);
		free(str);
		str = new_str;
	}
	else if (len > 1)
	{
		if (var_env)
			new_str = concat_str(str, var_env, i, len);
		else
			new_str = suppr_namevars(str, i, len);
		free(str);
		str = new_str;
	}
	return (str);
}

char	*import_varsenv(t_env *envlst, char *str, int i)
{
	int		len;
	char	*quote;
	char	*var_env;
	char	*name_var;

	while (str && str[i])
	{
		quote = quote_secur(str);
		var_env = NULL;
		if (str[i] == '$' && quote[i] != '2')
		{
			len = len_varsenv(str + i);
			if (len > 1 && ft_strncmp("$?", str + i, 2))
			{				
				name_var = ft_substr(str, i + 1, len - 1);
				var_env = ft_getenv(envlst, name_var);
				free(name_var);
			}
			str = import_varsenvbis(str, i, len, var_env);
		}
		free(quote);
		if (str[i])
			i++;
	}
	return (str);
}
