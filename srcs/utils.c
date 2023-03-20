/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:22:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/20 12:39:43 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * parses map_arr and prints out all values in the format
 * (x,y)z
 */
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
			ft_printf("(%i,%i)\033[35;1m%i\033[0m\t",
				(int)pt->x, (int)pt->y, (int)pt->z);
			clmn++;
		}
		printf("\n");
		row++;
	}
}

/**
 * frees split array
 */
void	*free_split_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		arr[i] = ft_free_set_null(arr[i]);
		i++;
	}
	arr = ft_free_set_null(arr);
	return (NULL);
}

/**
 * counts how many sub arrays there are in the split char** return value
 * this is needed to know how many values there are in a line in a map file
 */
int	n_sub_arr(char **s)
{
	int	n;

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

/**
 * if there is a line/split_line from previous gnl/split call, then they
 * are freed. fetches the next line with gnl and breaks them up with split
 * saved in input struct
 */
void	gnl_split(t_input *input)
{
	input->line = ft_free_set_null(input->line);
	input->split_line = free_split_arr(input->split_line);
	input->line = get_next_line(input->fd);
	input->split_line = ft_split(input->line, ' ');
}

/**
 * free the map struct, especially the map_arr aka each point
 */
t_map	*free_map(t_map *map, int nrows)
{
	int	row;
	int	clmn;

	if (!map && !(map->map_arr))
		return (NULL);
	row = 0;
	while (row < nrows)
	{
		clmn = 0;
		while (clmn < map->nclmns)
		{
			(map->map_arr)[row][clmn]
				= ft_free_set_null((map->map_arr)[row][clmn]);
			clmn++;
		}
		(map->map_arr)[row] = ft_free_set_null((map->map_arr)[row]);
		row++;
	}
	map->map_arr = ft_free_set_null(map->map_arr);
	map = ft_free_set_null(map);
	return (map);
}
