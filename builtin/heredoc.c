/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:05:17 by jhii              #+#    #+#             */
/*   Updated: 2022/06/21 20:31:41 by jhii             ###   ########.fr       */
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

static	void	here_doc(t_array *array, int prc, char **temp, int size)
{
	char	*temp1;
	char	*temp2;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		temp1 = get_next_line(0);
		if (ft_strcmp(temp1, temp[array->i]))
			array->i++;
		else if (array->i == size - 1)
		{
			temp2 = ft_strdup(array->cmd_group[prc].heredoc);
			if (array->cmd_group[prc].heredoc[0] != '\0')
				free(array->cmd_group[prc].heredoc);
			array->cmd_group[prc].heredoc = ft_strjoin(temp2, temp1);
			free(temp2);
		}
		if (array->i == size)
		{
			free(temp1);
			break ;
		}
		free(temp1);
	}
	array->i = 0;
}

static	void	get_heredoc(t_array *array, char **temp, int prc, int *j)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < array->cmd_group[prc].redir.size)
	{
		tmp = NULL;
		if (array->cmd_group[prc].redir.types[i] == HEREDOC)
		{
			tmp = ft_strdup(array->cmd_group[prc].redir.files[i]);
			temp[*j] = ft_strjoin(tmp, "\n");
			*j = *j + 1;
			free(tmp);
		}
		i++;
	}
}

void	save_heredoc(t_array *array, int prc)
{
	int		j;
	int		size;
	char	**temp;

	j = 0;
	size = heredoc_size(array, prc);
	if (size == 0)
		return ;
	temp = malloc(sizeof(char *) * size);
	get_heredoc(array, temp, prc, &j);
	here_doc(array, prc, temp, size);
	free_array(temp, size);
}
