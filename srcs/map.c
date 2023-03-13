/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:33:44 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/10 13:06:09 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	point->x = x * map->zoom + map->xoff;
	point->y = y * map->zoom + map->yoff;
	point->z = z * map->zoom;
	point->color = map->color;
	(map->map_arr)[y][x] = point;
	return (map);
}

t_map	*malloc_map_rows(t_map *map, t_input *input)
{
	input->line = get_next_line(input->fd);
	while (input->line)
	{
		free(input->line);
		map->nrows++;
		input->line = get_next_line(input->fd);
	}
	free(input->line);
	map->map_arr = malloc(sizeof(t_point) * map->nrows);
	if (!map->map_arr)
		return (perror("map_arr alloc failed"), NULL);
	close(input->fd);
	input->fd = open(input->map_file, O_RDONLY);
	if (!input->fd)
		return (NULL);
	return (map);
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
*/
t_map	*parse_map(t_map *map, t_input *input)
{
	input = gnl_split(input);
	map->nclmns = n_sub_arr(input->split_line);
	while (input->split_line && (map->nclmns == n_sub_arr(input->split_line)))
	{
		(map->map_arr)[input->y] = malloc(sizeof(t_point) * map->nclmns);
		if (!((map->map_arr)[input->y]))
			return (NULL);
		input->x = 0;
		while (input->split_line[input->x])
		{
			map = add_point(map, input->x, input->y,
				ft_atoi(input->split_line[input->x]));
			if (!map)
				return (NULL);
			(input->x)++;
		}
		input = gnl_split(input);
		(input->y)++;
	}
	free(input->line);
	free_split_arr(input->split_line);
	free(input->map_file);
	free(input);
	return (map);
}
