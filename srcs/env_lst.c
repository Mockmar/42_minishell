
#include "../incl/minishell.h"

int	env_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return (1);
	tmp = env_lstlast(*alst);
	if (tmp)
		tmp->next = new;
	else
		*alst = new;
	return (0);
}

t_env	*env_lstlast(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*env_lstnew(char *name)
{
	t_env	*element;

	element = malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->name = name;
	element->next = NULL;
	return (element);
}

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	env_lstclear(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst);
		lst = tmp;
	}
}
