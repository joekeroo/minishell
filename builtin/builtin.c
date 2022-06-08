/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:34:15 by jhii              #+#    #+#             */
/*   Updated: 2022/06/08 16:29:36 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin(t_array *array)
{
	echo(array);
	print_env(array, 0);
	export_env(array);
	unset_env(array);
	exit_minishell(array);
}
