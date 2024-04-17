#include "libft.h"

static t_list	*ft_lstmap2(t_list *lst, void *(*f)(void *),
			void (del)(void *), t_list *newlst)
{
	t_list	*newelem;

	newelem = ft_lstnew(f(lst->content));
	if (!newelem)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	newlst = newelem;
	lst = lst->next;
	while (lst)
	{
		newelem = ft_lstnew(f(lst->content));
		if (!newelem)
		{
			ft_lstclear(&newlst, del);
			ft_lstclear(&lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, newelem);
	}
	return (newlst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;

	if (!f || !lst)
		return (NULL);
	newlst = NULL;
	newlst = ft_lstmap2(lst, f, del, newlst);
	return (newlst);
}
