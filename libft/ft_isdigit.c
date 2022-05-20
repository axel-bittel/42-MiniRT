/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:09:04 by abittel           #+#    #+#             */
/*   Updated: 2021/08/05 18:16:15 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1 << 10);
	return (0);
}

int	ft_str_isdigit(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if ((str[i] != '-') && (str[i] != '+') && !ft_isdigit(str[i]))
		return (0);
	while (str[++i])
	{
		if (str[i] == '.')
			dot++;
		if ((!ft_isdigit(str[i]) && (str[i] != '.')) || dot > 1)
			return (0);
	}
	return (1);
}
