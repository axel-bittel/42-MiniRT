/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:19:05 by abittel           #+#    #+#             */
/*   Updated: 2021/10/25 17:32:17 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*inter;
	t_list	*inter2;

	inter = *lst;
	while (inter->next != NULL)
	{
		inter2 = (t_list *)inter->next;
		del(inter->content);
		free(inter);
		inter = inter2;
	}
	del(inter->content);
	free(inter);
	*lst = NULL;
}
