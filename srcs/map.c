/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:33:44 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/05 12:28:51 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_map(t_map *map)
{
	t_point	*pt;

	pt = map->origin;
	while (pt)
	{
		printf("x:%i y:%i, z:%i\n", pt->x, pt->y, pt->z);
		pt = pt->next;
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
t_map	*parse_map(int fd)
{
	int		x;
	int		y;
	char	**row;
	t_map	*map;
	
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	y = 0;
	row = ft_split(get_next_line(fd), ' ');
	while (row)
	{
		x = 0;
		while (row[x])
		{
			map = add_point(map, x, y, ft_atoi(row[x]));
			if (!map)
				return (NULL);
			x++;
		}
		y++;
		row = ft_split(get_next_line(fd), ' ');
	}
	return (map);
}
