/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:40:47 by abittel           #+#    #+#             */
/*   Updated: 2022/05/19 11:09:31 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	map_key_one(int keycode)
{
	if (keycode == KEY_A)
		return ('a');
	if (keycode == KEY_B)
		return ('b');
	if (keycode == KEY_C)
		return ('c');
	if (keycode == KEY_D)
		return ('d');
	if (keycode == KEY_E)
		return ('e');
	if (keycode == KEY_F)
		return ('f');
	if (keycode == KEY_G)
		return ('g');
	if (keycode == KEY_H)
		return ('h');
	if (keycode == KEY_I)
		return ('i');
	if (keycode == KEY_J)
		return ('j');
	return (keycode);
}

int	map_key_two(int keycode)
{
	if (keycode == KEY_K)
		return ('k');
	if (keycode == KEY_L)
		return ('l');
	if (keycode == KEY_M)
		return ('m');
	if (keycode == KEY_N)
		return ('n');
	if (keycode == KEY_O)
		return ('o');
	if (keycode == KEY_P)
		return ('p');
	if (keycode == KEY_Q)
		return ('q');
	if (keycode == KEY_R)
		return ('r');
	if (keycode == KEY_S)
		return ('s');
	if (keycode == KEY_T)
		return ('t');
	if (keycode == KEY_U)
		return ('u');
	return (keycode);
}

int	map_key_three(int keycode)
{
	if (keycode == KEY_V)
		return ('v');
	if (keycode == KEY_W)
		return ('w');
	if (keycode == KEY_X)
		return ('x');
	if (keycode == KEY_Y)
		return ('y');
	if (keycode == KEY_Z)
		return ('z');
	if (keycode == KEY_EQUAL)
		return ('=');
	if (keycode == KEY_SPACE)
		return (' ');
	if (keycode == KEY_VIRG)
		return (',');
	if (keycode == KEY_DOT)
		return ('.');
	if (keycode == 36)
		return (65293);
	if (keycode == 53)
		return (65307);
	if (keycode == KEY_ZERO)
		return ('0');
	return (keycode);
}

int	map_key_four(int keycode)
{
	if (keycode == KEY_ONE)
		return ('1');
	if (keycode == KEY_TWO)
		return ('2');
	if (keycode == KEY_THREE)
		return ('3');
	if (keycode == KEY_FOUR)
		return ('4');
	if (keycode == KEY_FIVE)
		return ('5');
	if (keycode == KEY_SIX)
		return ('6');
	if (keycode == KEY_SEVEN)
		return ('7');
	if (keycode == KEY_EIGHT)
		return ('8');
	if (keycode == KEY_NINE)
		return ('9');
	if (keycode == KEY_DELETE)
		return (65288);
	if (keycode == KEY_TIRET)
		return ('-');
	return (keycode);
}

int	map_key(int keycode)
{
	int	inter;

	inter = map_key_one(keycode);
	if (inter != keycode)
		return (inter);
	inter = map_key_two(keycode);
	if (inter != keycode)
		return (inter);
	inter = map_key_three(keycode);
	if (inter != keycode)
		return (inter);
	inter = map_key_four(keycode);
	if (inter != keycode)
		return (inter);
	return (keycode);
}
