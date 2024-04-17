#include "libft.h"

static void	memmove2(unsigned char *s, unsigned char *d, size_t len)
{
	size_t	i;

	if (d < s)
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i + 1)
		{
			d[i] = s[i];
			i--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	memmove2(s, d, len);
	return (dst);
}
