/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:33:59 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/16 18:05:14 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * pointd struct is used for calculations (floating values)
 * after projection values are rounded back to ints
*/
void	*project_point(t_point *point, t_map *map)
{
	rotate_zaxis(point, (double)map->zdeg * DEG2RAD);
	rotate_yaxis(point, (double)map->ydeg * DEG2RAD);
	rotate_xaxis(point, (double)map->xdeg * DEG2RAD);
	return (map);
}

void	*translate_point(t_point *point, t_map *map)
{
	point->x += map->xoff;
	point->y += map->yoff;
	return (map);
}

void	*zoom_point(t_point *point, t_map *map)
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
	return (map);
}

void	*random_point_color(t_point *point, t_map *map)
{
	point->color = ft_random(0xFF000000, 0x00FF0000);
	return (map);
}

void	*point_color(t_point *point, t_map *map)
{
	point->color = map->color;
	return (map);
}

void	*reset(t_point *point, t_map *map)
{
	point->x = point->x_init;
	point->y = point->y_init;
	point->z = point->z_init;
	return (map);
}
