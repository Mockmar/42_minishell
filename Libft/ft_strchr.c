#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == uc)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == uc)
		return ((char *)(s + i));
	return (NULL);
}
