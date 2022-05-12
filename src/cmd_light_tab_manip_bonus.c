/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_light_tab_manip_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:19:53 by abittel           #+#    #+#             */
/*   Updated: 2022/04/23 13:13:15 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include <unistd.h>
#include <stdlib.h>

t_ligth	**add_tab_light(t_ligth **tab, t_ligth *new)
{
	int		i;
	t_ligth	**res;

	i = 0;
	while (tab && tab[i])
		i++;
	res = malloc (sizeof(t_ligth *) * (i + 2));
	res[i + 1] = NULL;
	i = 0;
	while (tab && tab[i])
	{
		res[i] = tab[i];
		i++;
	}
	res[i] = new;
	free(tab);
	return (res);
}

void	free_tab_ligth(t_ligth **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}
