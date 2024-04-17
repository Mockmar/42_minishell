
#include "../incl/minishell.h"

int	len_tab(char **cmd)
{
	int	cpt;

	cpt = 0;
	while (cmd && cmd[cpt])
		cpt++;
	return (cpt);
}

char	*trim_str(char *cmd)
{
	char	*qot;
	char	*str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	str = NULL;
	qot = quote_secur(cmd);
	while (cmd[j])
	{
		if (qot[j] != '0' || (cmd[j] != '\'' && cmd[j] != '\"'))
		{
			str = ft_straddchar(str, cmd[j]);
			k++;
		}
		j++;
	}
	if (!k)
		str = malloc(sizeof(char *));
	if (!str)
		return (NULL);
	str[k] = 0;
	free(qot);
	return (str);
}

char	**alloc_tab(char **tab, char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		tab[i] = trim_str(cmd[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**trim_cmd(char **cmd)
{
	char	**tab;

	tab = (char **)malloc(sizeof(*tab) * (len_tab(cmd) + 1));
	if (!tab)
		return (NULL);
	tab = alloc_tab(tab, cmd);
	return (tab);
}
