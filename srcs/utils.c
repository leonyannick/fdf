/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:22:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/10 12:54:45 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_map(t_map *map)
{
	int		row;
	int		clmn;
	t_point	*pt;

	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < map->nclmns)
		{
			pt = (map->map_arr)[row][clmn];
			printf("(%i,%i)\033[35;1m%i\033[0m\t", pt->x, pt->y, pt->z);
			clmn++;
		}
		printf("\n");
		row++;
	}
}

void	free_split_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	n_sub_arr(char **s)
{
	int		n;

	n = 0;
	if (!s)
		return (n);
	while (*s)
	{
		s++;
		n++;
	}
	return (n);
}

t_input	*gnl_split(t_input *input)
{
	if (input->line)
		free(input->line);
	if (input->split_line)
		free_split_arr(input->split_line);
	input->line = get_next_line(input->fd);
	input->split_line = ft_split(input->line, ' ');
	return (input);
}

