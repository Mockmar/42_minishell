
#include "libft.h"

static char	*if_strempty(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = 0;
	return (str);
}

char	*ft_straddchar(char *s1, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	if (!s1)
		return (if_strempty(c));
	len = ft_strlen(s1) + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(s1);
	return (str);
}
