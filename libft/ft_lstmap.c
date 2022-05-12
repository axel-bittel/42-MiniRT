/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:28:30 by abittel           #+#    #+#             */
/*   Updated: 2021/10/25 17:33:26 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*inter;
	t_list	*res;
	t_list	*content;

	if (!lst | !f)
		return (NULL);
	res = 0;
	inter = lst;
	while (inter->next != NULL)
	{
		content = ft_lstnew(f(inter->content));
		if (!content)
		{
			ft_lstclear(&res, del);
			break ;
		}
		if (!res)
			res = content;
		else
			ft_lstadd_back(&res, content);
		inter = (t_list *)inter->next;
	}
	ft_lstadd_back(&res, ft_lstnew(f(inter->content)));
	return (res);
}
