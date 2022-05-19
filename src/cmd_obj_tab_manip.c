/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_obj_tab_manip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:57:09 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 11:09:52 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	**add_tab_obj(t_obj **tab, t_obj *new)
{
	int		i;
	t_obj	**res;

	i = 0;
	while (tab && tab[i])
		i++;
	res = malloc (sizeof(t_obj *) * (i + 2));
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

void	free_obj(t_obj *obj)
{
	if (obj->type == TYPE_SPHERE)
		free((t_sphere *)obj->obj);
	if (obj->type == TYPE_PLANE)
		free((t_plane *)obj->obj);
	if (obj->type == TYPE_CYLINDER)
		free((t_cylinder *)obj->obj);
	free(obj);
}

t_obj	**delete_tab_obj(t_obj **tab, int idx)
{
	int		i;
	int		j;
	t_obj	**res;

	i = 0;
	while (tab[i])
		i++;
	if (idx < 0 || idx > i - 1)
		return (tab);
	res = malloc (sizeof(t_obj *) * (i));
	res[i - 1] = NULL;
	i = -1;
	j = -1;
	while (tab[++i])
	{
		if (i != idx)
			res[++j] = tab[i];
	}
	free_obj(tab[idx]);
	free(tab);
	return (res);
}

void	free_tab_obj(t_obj **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free_obj(tab[i]);
	free(tab);
}
