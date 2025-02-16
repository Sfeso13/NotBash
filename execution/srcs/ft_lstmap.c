#include "../includes/exec.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nl;
	t_list	*tmp;

	if (lst && del && f)
	{
		nl = ft_lstnew(f(lst->content));
		if (nl == NULL)
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			tmp = ft_lstnew(f(lst->content));
			if (!tmp)
			{
				ft_lstclear(&tmp, del);
				return (NULL);
			}
			ft_lstadd_back(&nl, tmp);
			lst = lst->next;
		}
		return (nl);
	}
	return (NULL);
}
