/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:33:59 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/09 11:16:29 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * pointd struct is used for calculations (floating values)
 * after projection values are rounded back to ints
*/
t_point	*project_point(t_point *point, t_map *map)
{
	t_pointd	*temp;

	temp = malloc(sizeof(t_pointd));
	if (!temp)
		return (NULL);
	temp->x = (double)point->x;
	temp->y = (double)point->y;
	temp->z = (double)point->z;
	temp = rotate_yaxis(temp, (double)map->ydeg * DEG2RAD);
	temp = rotate_xaxis(temp, (double)map->xdeg * DEG2RAD);
	// temp = projection_to_2d(temp);
	point->x = (int)round(temp->x);
	point->y = (int)round(temp->y);
	point->z = (int)temp->z;
	free(temp);
	return (point);
}

t_point	*translate_point(t_point *point, t_map *map)
{
	point->x += map->xoff;
	point->y += map->yoff;
	return (point);
}

t_point	*zoom_point(t_point *point, t_map *map)
{
	if (map->zoom)
	{
		point->x *= S_ZOOM;
		point->y *= S_ZOOM;
	}
	else
	{
		point->x /= S_ZOOM;
		point->y /= S_ZOOM;
	}
	return (point);
}

t_map	*change_points(t_map *map, t_point *(*f)(t_point *point, t_map *map))
{
	int		row;
	int		clmn;

	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < (map->nclmns))
		{
			(map->map)[row][clmn] = (*f)((map->map)[row][clmn], map);
			clmn++;
		}
		row++;
	}
	connect_the_dots(map);
	return (map);
}
