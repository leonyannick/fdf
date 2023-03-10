/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:33:44 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/10 11:23:01 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

/**
 * creates a point and assigns x,y,z and links points as a singly linked list.
 * saves origin (0,0) in map struct
*/
t_map	*add_point(t_map *map, int x, int y, int z)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x * ZOOM + XOFF;
	point->y = y * ZOOM + YOFF;
	point->z = z * ZOOM;
	point->color = P_COLOR;
	(map->map)[y][x] = point;
	return (map);
}

t_map	*init_map_attributes(t_map *map)
{
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->zoom = 0;
	map->xoff = 0;
	map->yoff = 0;
	map->xdeg = 0;
	map->ydeg = 0;
	map->clr_int = false;
	return (map);
}

t_map	*init_map(t_map *map, t_input *input, char *map_name)
{
	int		nrows;

	map = init_map_attributes(map);
	if (!map)
		return (NULL);
	nrows = 0;
	input->line = get_next_line(input->fd);
	while (input->line)
	{
		free(input->line);
		nrows++;
		input->line = get_next_line(input->fd);
	}
	map->map = malloc(sizeof(t_point) * nrows);
	if (!map->map)
		return (NULL);
	map->nrows = nrows;
	close(input->fd);
	free(input->line);
	free(input);
	input = init_input(input, map_name);
	if (!input)
		return (NULL);
	return (parse_map(map, input));
}

static int	n_sub_arr(char **s)
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

/**
 * - parses the map from the input file
 * 
 * (x, y)
 * --> [x]	(0,0) (1,0) (2,0) (3,0)
 * |		(0,1) (1,1) (2,1) (3,1)
 * V		(0,2) (1,2) (2,2) (3,2)
 *[y]		(0,3) (1,3) (2,3) (3,3)
 * The horizontal position corresponds to its axis (x-axis).
 * The vertical position corresponds to its ordinate (y-axis).
 * The value corresponds to its altitude.
 * 
 * @param fd file descriptor to the map file
*/
t_map	*parse_map(t_map *map, t_input *input)
{
	input->line = get_next_line(input->fd);
	input->row = ft_split(input->line, ' ');
	map->nclmns = n_sub_arr(input->row);
	while (input->row && (map->nclmns == n_sub_arr(input->row)))
	{
		(map->map)[input->y] = malloc(sizeof(t_point) * map->nclmns);
		if (!((map->map)[input->y]))
			return (NULL);
		input->x = 0;
		while (input->row[input->x])
		{
			map = add_point(map, input->x, input->y, ft_atoi(input->row[input->x]));
			if (!map)
				return (NULL);
			(input->x)++;
		}
		(input->y)++;
		free(input->line);
		free_split_arr(input->row);
		input->line = get_next_line(input->fd);
		input->row = ft_split(input->line, ' ');
	}
	return (free(input->line), free_split_arr(input->row), free(input), map);
}
