/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:07:24 by jhii              #+#    #+#             */
/*   Updated: 2022/05/28 17:18:34 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	unsigned int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		printf("%s\n", array[i++]);
}

void	free_cmdgrp(t_array *array)
{
	int	i;

	i = 0;
	while (i < array->n_cmdln)
	{
		if (array->cmd_group[i].infile)
			free(array->cmd_group[i].infile);
		if (array->cmd_group[i].outfile)
			free(array->cmd_group[i].outfile);
		free_array(array->cmd_group[i++].cmd);
	}
	free(array->cmd_group);
}

void	print_cmdln(t_array *array)
{
	int	i;
	int	j;

	i = 0;
	while (i < array->n_cmdln)
	{
		j = 0;
		printf("\n");
		printf("infile = %s\n", array->cmd_group[i].infile);
		printf("outfile = %s\n", array->cmd_group[i].outfile);
		printf("[");
		while (array->cmd_group[i].cmd[j])
		{
			printf("%s", array->cmd_group[i].cmd[j++]);
			if (array->cmd_group[i].cmd[j])
				printf(", ");
		}
		printf("]\n\n");
		i++;
	}
}
