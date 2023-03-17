/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:33:44 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 09:56:33 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * creates a point and assigns x,y,z with the initial values for zoom and
 * yoff/xoff (from macros in header file). saves the initial values in init 
 * variable, so they can be restored later
*/
t_map	*add_point(t_map *map, int x, int y, int z)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x_init = x * ZOOM + XOFF;
	point->y_init = y * ZOOM + YOFF;
	point->z_init = z * ZOOM;
	point->x = point->x_init;
	point->y = point->y_init;
	point->z = point->z_init;
	point->color = P_COLOR;
	(map->map_arr)[y][x] = point;
	return (map);
}

/**
 * goes through file with gnl and counts how many rows there are, so that
 * map_arr can be allocated accordingly. after parsing file is closed and
 * opened again, for actual data copying in parse_map function
*/
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
	map->map_arr = malloc(sizeof(t_point *) * map->nrows);
	if (!map->map_arr)
		return (perror("map_arr alloc failed"), NULL);
	close(input->fd);
	input->fd = open(input->map_file, O_RDONLY);
	if (!input->fd)
		return (NULL);
	input->line = NULL;
	input->split_line = NULL;
	return (map);
}

/**
 * parses the map from the input file and saves each point in map_arr.
 * gnl is used to fetch each line, split is used to break up the line
 * in the individual numbers that are converted from char to int with
 * atoi. returns from gnl and split have to be saved in variables, to
 * be able to free the memory after having saved the data. input struct
 * is freed after parsing, because it is not used afterwards
 * 
 * file structure:
 * (x, y)
 * --> [x]	(0,0) (1,0) (2,0) (3,0)
 * |		(0,1) (1,1) (2,1) (3,1)
 * V		(0,2) (1,2) (2,2) (3,2)
 *[y]		(0,3) (1,3) (2,3) (3,3)
 * The horizontal position corresponds to its axis (x-axis).
 * The vertical position corresponds to its ordinate (y-axis).
 * The value corresponds to its altitude.
 * 
 * map_arr structure:
 * map_arr[y][x]
*/
t_map	*parse_map(t_map *map, t_input *input)
{
	gnl_split(input);
	map->nclmns = n_sub_arr(input->split_line);
	while (input->split_line)
	{
		if (map->nclmns != n_sub_arr(input->split_line))
			return (perror("unregular number of elements in line"), NULL);
		(map->map_arr)[input->y] = malloc(sizeof(t_point) * map->nclmns);
		if (!((map->map_arr)[input->y]))
			return (NULL);
		input->x = 0;
		while (input->split_line[input->x])
		{
			if (!add_point(map, input->x, input->y,
					ft_atoi(input->split_line[input->x])))
				return (NULL);
			(input->x)++;
		}
		gnl_split(input);
		(input->y)++;
	}
	free(input->line);
	free_split_arr(input->split_line);
	free(input->map_file);
	free(input);
	return (map);
}
