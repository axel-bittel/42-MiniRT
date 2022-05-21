/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:08:35 by abittel           #+#    #+#             */
/*   Updated: 2022/05/21 12:06:28 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_datas	*data;

	if (argc == 2)
	{
		data = init_mymlx();
		check_file_ext(argv[1], data);
		parse_file(argv[1], data);
		refresh_screen(data);
		mlx_hook(data->mlx_win, X_EVENT_KEY_PRESS, 1L << 0, press_key, data);
		mlx_hook(data->mlx_win, EXIT_CROSS, 1L << 17, close_win, data);
		mlx_loop(data->mlx);
	}
	else
		ft_putstr_fd("ARG NUMBER ERROR !\n", 1);
	return (0);
}
