#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (s[i])
		i++;
	if (s[i] == uc)
		return ((char *)(s + i));
	while (i >= 0)
	{
		if (s[i] == uc)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
