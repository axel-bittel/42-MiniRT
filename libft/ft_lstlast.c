/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:06:31 by abittel           #+#    #+#             */
/*   Updated: 2021/10/25 17:33:14 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stddef.h>

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*inter;

	inter = lst;
	if (!lst)
		return (NULL);
	while (inter->next != NULL)
		inter = (t_list *)inter->next;
	return (inter);
}
