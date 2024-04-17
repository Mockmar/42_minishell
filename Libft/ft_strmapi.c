#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_tmp;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	s_tmp = malloc(sizeof(*s_tmp) * (i + 1));
	if (!s_tmp)
		return (NULL);
	s_tmp[i] = 0;
	i = 0;
	while (s[i])
	{
		s_tmp[i] = (*f)((unsigned int)i, s[i]);
		i++;
	}
	return (s_tmp);
}
