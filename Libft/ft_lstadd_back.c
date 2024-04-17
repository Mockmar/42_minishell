#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = ft_lstlast(*alst);
	if (tmp)
		tmp->next = new;
	else
		*alst = new;
}
