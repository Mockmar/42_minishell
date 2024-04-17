
#include "../incl/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	print_msg(int fd, char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, fd);
	if (s2)
		ft_putstr_fd(s2, fd);
	if (s3)
		ft_putstr_fd(s3, fd);
	return (1);
}
