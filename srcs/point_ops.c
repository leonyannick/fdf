/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:33:59 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/14 14:50:30 by lbaumann         ###   ########.fr       */
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
	rotate_yaxis(temp, (double)map->ydeg * DEG2RAD);
	rotate_xaxis(temp, (double)map->xdeg * DEG2RAD);
	point->x = (int)(temp->x);
	point->y = (int)(temp->y);
	point->z = (int)(temp->z);
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
		point->x = (int)((float)point->x * S_ZOOM);
		point->y = (int)((float)point->y * S_ZOOM);
	}
	else
	{
		point->x = (int)((float)point->x / S_ZOOM);
		point->y = (int)((float)point->y / S_ZOOM);
	}
	return (point);
}

t_point	*random_point_color(t_point *point, t_map *map)
{
	point->color = ft_random(0xFF000000, 0x00FF0000);
	return (point);
}

t_point	*point_color(t_point *point, t_map *map)
{
	point->color = map->color;
	return (point);
}

t_data	*paint_pixels(t_data *data, t_point *(*f)(t_point *point, t_map *map))
{
	int		row;
	int		clmn;

	row = 0;
	while (row < data->map->nrows)
	{
		clmn = 0;
		while (clmn < (data->map->nclmns))
		{
			(data->map->map_arr)[row][clmn]
				= (*f)((data->map->map_arr)[row][clmn], data->map);
			clmn++;
		}
		row++;
	}
	connect_the_dots(data);
	return (data);
}
