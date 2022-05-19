/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_light_tab_manip_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:19:53 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 11:09:40 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	**add_tab_light(t_light **tab, t_light *new)
{
	int		i;
	t_light	**res;

	i = 0;
	while (tab && tab[i])
		i++;
	res = malloc (sizeof(t_light *) * (i + 2));
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

void	free_tab_ligth(t_light **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}
