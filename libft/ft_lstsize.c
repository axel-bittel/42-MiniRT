/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:03:39 by abittel           #+#    #+#             */
/*   Updated: 2021/10/25 17:33:51 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*inter;

	i = 0;
	inter = lst;
	if (!lst)
		return (0);
	while (inter->next != NULL)
	{
		i = i + 1;
		inter = (t_list *)inter->next;
	}
	i += 1;
	return (i);
}
