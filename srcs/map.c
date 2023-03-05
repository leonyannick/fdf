/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:33:44 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/05 17:56:31 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_map(t_map *map)
{
	int		row;
	int		clmn;
	t_point	*pt;

	row = 0;
	while (row <= map->nrows)
	{
		while (clmn <= map->map)
		{
			pt = map->map[clmn][row];
			printf("x:%i y:%i, z:%i\n", pt->x, pt->y, pt->z);
			clmn++;
		}
		row++;
	}
}

/**
 * creates a point and assigns x,y,z and links points as a singly linked list.
 * saves origin (0,0) in map struct
*/
t_map	*add_point(t_map *map, int x, int y, int z)
{
	t_point	*point;
	t_point	*prev;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	if (x == 0 && y == 0)
		map->origin = point;
	prev = map->origin;
	while (prev->next)
		prev = prev->next;
	prev->next = point;
	point->x = x;
	point->y = y;
	point->z = z;
	point->next = NULL;
	return (map);
}

t_map	*init_map(t_map *map, int fd)
{
	int		nrows;
	
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	nrows = 0;
	while (get_next_line(fd))
		nrows++;
	map->map = malloc(sizeof(t_point) * nrows);
	if (!map->map)
		return (NULL);
	map->nrows = nrows;
	close(fd);
	return (map);
}

static int	n_sub_arr(char **s)
{
	int		n;

	n = 0;
	while (s)
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
t_map	*parse_map(int fd, char *map_name)
{
	int		x;
	int		y;
	char	**row;
	int		nclmns;
	t_map	*map;
	
	map = init_map(map, fd);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	y = 0;
	row = ft_split(get_next_line(fd), ' ');
	nclmns = n_sub_arr(row);
	while (row)
	{
		x = 0;
		(map->map)[y] = malloc(sizeof(t_point) * nclmns);
		if (!((map->map)[y]))
			return (NULL);
		while (row[x])
		{
			add_point(map, x, y, ft_)
			x++;
		}
		y++;
		row = ft_split(get_next_line(fd), ' ');
		nclmns = n_sub_arr(row);
	}
	return (map);
}
