
#include "libft.h"

char	**ft_tabaddstr(char **tab, char *add)
{
	int		len;
	char	**ret;

	len = 0;
	if (!tab)
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = add;
		ret[1] = NULL;
		return (ret);
	}
	while (tab[len] != NULL)
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	ret[len + 1] = NULL;
	ret[len] = add;
	while (len != 0)
	{
		ret[len - 1] = tab[len - 1];
		len --;
	}
	free(tab);
	return (ret);
}
