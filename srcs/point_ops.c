/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:33:59 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 10:13:56 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * applies the rotation matrices for each axis x, y, z with
 * the specified angle saved in the map struct
*/
void	*project_point(t_point *point, t_map *map)
{
	rotate_zaxis(point, (double)map->zdeg * DEG2RAD);
	rotate_yaxis(point, (double)map->ydeg * DEG2RAD);
	rotate_xaxis(point, (double)map->xdeg * DEG2RAD);
	return (map);
}

/**
 * translates point with offset specified in map struct
*/
void	*translate_point(t_point *point, t_map *map)
{
	point->x += map->xoff;
	point->y += map->yoff;
	return (map);
}

/**
 * applies zoom with stepsize from header file
*/
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

/**
 * assigns each point a random calor value within the specified
 * integer range (min and max)
*/
void	*random_point_color(t_point *point, t_map *map)
{
	point->color = ft_random(0xFF000000, 0x00FF0000);
	return (map);
}

/**
 * resets points to their initial values after file was parsed
 * and before isometric projection
*/
void	*reset(t_point *point, t_map *map)
{
	point->x = point->x_init;
	point->y = point->y_init;
	point->z = point->z_init;
	return (map);
}
