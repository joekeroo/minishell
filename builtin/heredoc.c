/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:05:17 by jhii              #+#    #+#             */
/*   Updated: 2022/06/17 14:53:04 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	heredoc_size(t_array *array, int prc)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < array->cmd_group[prc].redir.size)
	{
		if (array->cmd_group[prc].redir.types[i] == HEREDOC)
			size++;
		i++;
	}
	return (size);
}

static	int	check_conditions(t_array *array, char *needle, char **stk, int sz)
{
	if (array->i == sz - 1)
	{
		if (ft_strcmp(needle, stk[array->i]))
			return (2);
		else
			return (1);
	}
	else
	{
		if (ft_strcmp(needle, stk[array->i]))
			array->i++;
		return (0);
	}
}

static	void	here_doc(t_array *array, char **temp, int size, int prc)
{
	char	*temp1;
	char	*temp2;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		temp1 = get_next_line(0);
		temp2 = ft_strdup(array->cmd_group[prc].heredoc);
		if (check_conditions(array, temp1, temp, size) == 1)
		{
			if (array->cmd_group[prc].heredoc[0] != '\0')
				free(array->cmd_group[prc].heredoc);
			array->cmd_group[prc].heredoc = ft_strjoin(temp2, temp1);
		}
		else if (check_conditions(array, temp1, temp, size) == 2)
		{
			free(temp1);
			free(temp2);
			break ;
		}
		free(temp1);
		free(temp2);
	}
	array->i = 0;
}

void	save_heredoc(t_array *array, int prc)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;
	char	**temp;

	i = 0;
	j = 0;
	size = heredoc_size(array, prc);
	if (size == 0)
		return ;
	temp = malloc(sizeof(char *) * size);
	while (i < array->cmd_group[prc].redir.size)
	{
		tmp = NULL;
		if (array->cmd_group[prc].redir.types[i] == HEREDOC)
		{
			tmp = ft_strdup(array->cmd_group[prc].redir.files[i]);
			temp[j++] = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		i++;
	}
	here_doc(array, temp, size, prc);
	free_array(temp, size);
}