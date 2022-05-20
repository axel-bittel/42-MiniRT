/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:04:12 by abittel           #+#    #+#             */
/*   Updated: 2022/05/20 19:57:55 by rahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PARSE_H
# define CMD_PARSE_H

int		check_cmd(t_datas *data, char **cmd_splt, int type_cmd);
int		check_cmd_change_args(t_datas *data, char **cmd_splt);
int		check_cmd_change_args_name(char **cmd_splt, int type, int idx);
int		check_cmd_add_args(char **cmd_splt);
int		check_cmd_add_args_names(char **cmd_splt);
char	**get_arg_change_names(char ***names, int type, int idx);
int		is_valid_arg(char *cmd_splt, char **names);
int		is_valid_arg_value(char *arg, char *name);
int		print_cmd_error(size_t err);

#endif
