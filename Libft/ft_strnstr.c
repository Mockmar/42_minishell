#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;
	char	*str_tmp;

	str_tmp = (char *)str;
	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str_tmp);
	while (str[i] && i < n)
	{
		j = 0;
		while (str_tmp[i + j] == to_find[j] && i + j < n)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)(str_tmp + i));
			j++;
		}
		i++;
	}
	return (0);
}
