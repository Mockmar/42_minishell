#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	char	*tmp;

	tmp = (char *)src;
	len = ft_strlen(tmp);
	if (len + 1 < size)
	{
		ft_memcpy(dst, src, len + 1);
	}
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len);
}
