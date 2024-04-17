
#include "libft.h"

static int	ft_cpt(int n)
{
	int	cpt;

	cpt = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		cpt++;
	}
	return (cpt);
}

static char	*malloc_neg(int n)
{
	char			*nbre;
	unsigned int	unsigned_n;
	int				i;

	i = 0;
	nbre = malloc(sizeof(*nbre) * (ft_cpt(n) + 2));
	if (!nbre)
		return (NULL);
	nbre[0] = '-';
	i = ft_cpt(n) + 1;
	nbre[i] = 0;
	unsigned_n = -n;
	while (unsigned_n > 0 && nbre[i] != '-' && i >= 0)
	{
		nbre[i - 1] = 48 + unsigned_n % 10;
		i--;
		unsigned_n /= 10;
	}
	return (nbre);
}

static char	*malloc_pos(int n)
{
	char			*nbre;
	unsigned int	unsigned_n;
	int				i;

	i = 0;
	nbre = malloc(sizeof(*nbre) * (ft_cpt(n) + 1));
	if (!nbre)
		return (NULL);
	i = ft_cpt(n);
	nbre [i] = 0;
	unsigned_n = n;
	while (unsigned_n > 0 && nbre[i] != '-' && i >= 0)
	{
		nbre[i - 1] = 48 + unsigned_n % 10;
		i--;
		unsigned_n /= 10;
	}
	return (nbre);
}

static char	*malloc_nul(void)
{
	char	*nbre;

	nbre = malloc(sizeof(*nbre) * 2);
	if (!nbre)
		return (NULL);
	nbre[0] = '0';
	nbre[1] = 0;
	return (nbre);
}

char	*ft_itoa(int n)
{
	char			*nbre;

	if (n == 0)
	{
		nbre = malloc_nul();
		if (!nbre)
			return (NULL);
		return (nbre);
	}
	else if (n < 0)
	{
		nbre = malloc_neg(n);
		if (!nbre)
			return (NULL);
	}
	else
	{
		nbre = malloc_pos(n);
		if (!nbre)
			return (NULL);
	}
	return (nbre);
}
