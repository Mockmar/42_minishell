
#include "../incl/minishell.h"

static int	compteur(char const *s, int mode, int i, char *qot)
{
	int	j;
	int	cpt;

	cpt = 0;
	j = 0;
	if (!mode)
		j = i;
	while (qot[j] && s[j])
	{
		while (qot[j] && s[j] && (s[j] == ' ' && qot[j] == '0'))
			j++;
		while (qot[j] && s[j] && (s[j] != ' ' || qot[j] != '0'))
		{
			if ((mode && cpt == 0)
				|| (mode && j > 1 && s[j - 1] == ' ' && qot[j - 1] == '0'))
				cpt++;
			else if (!mode)
				cpt++;
			j++;
		}
		if (!mode)
			return (cpt);
	}
	return (cpt);
}

static char	**malloc_tabs(char **tab, char const *s, char *qot)
{
	int	i;
	int	j;
	int	cpt;

	i = 0;
	j = 0;
	while (qot[i] && s[i])
	{
		while (s[i] && qot[i] && s[i] == ' ' && qot[i] == '0')
			i++;
		cpt = compteur(s, 0, i, qot);
		if (cpt)
		{
			tab[j] = malloc(sizeof(char) * (cpt + 1));
			i += cpt;
			if (!tab[j])
				return (NULL);
			tab[j][cpt] = 0;
		}
		j++;
	}
	return (tab);
}

static char	**ft_copy_split(char **tab, char const *s, char *qot)
{
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	while (qot[k] && s[k])
	{
		j = 0;
		while (qot[k] && s[k] && s[k] == ' ' && qot[k] == '0')
			k++;
		while (s[k] && qot[k] && (s[k] != ' ' || qot[k] != '0'))
		{
			tab[i][j] = s[k];
			k++;
			j++;
		}
		i++;
	}
	return (tab);
}

char	**ft_split_cmd(char const *s)
{
	char	**tab;
	int		cpt;
	char	*qot;

	if (!s)
		return (NULL);
	qot = quote_secur((char *)s);
	cpt = compteur(s, 1, 0, qot);
	tab = (char **)malloc(sizeof(*tab) * (cpt + 1));
	if (!(tab))
		return (NULL);
	tab = malloc_tabs(tab, s, qot);
	if (!(tab))
		return (NULL);
	tab = ft_copy_split(tab, s, qot);
	tab[cpt] = NULL;
	free(qot);
	return (tab);
}
