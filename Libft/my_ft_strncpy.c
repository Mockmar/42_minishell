
#include "libft.h"

char	*my_ft_strncpy(char *dest, char *src, int n)
{
	int	i;
	int	len;

	i = 0;
	if (n > ft_strlen(src))
		len = ft_strlen(src);
	else
		len = n;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
