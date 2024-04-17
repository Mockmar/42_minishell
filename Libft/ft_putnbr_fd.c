#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = (unsigned int)-n;
	}
	else
		nb = (unsigned int)n;
	if (nb < 10)
		ft_putchar_fd(48 + nb, fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(48 + nb % 10, fd);
		nb /= 10;
	}
}
