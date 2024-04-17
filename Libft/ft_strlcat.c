#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	j;

	lendst = ft_strlen(dst);
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= lendst)
		return (dstsize + ft_strlen(src));
	while (src[j] && j + lendst + 1 < dstsize)
	{
		dst[j + lendst] = src[j];
		j++;
	}
	dst[j + lendst] = 0;
	return (lendst + ft_strlen(src));
}
