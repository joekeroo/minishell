/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:08:12 by jhii              #+#    #+#             */
/*   Updated: 2022/06/06 12:02:19 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(t_array *array)
{
	init_cmdgrp(array);
	check_expansion(array);
	check_files(array);
	check_cmd(array);
	check_args(array);
	print_cmdln(array);
}
