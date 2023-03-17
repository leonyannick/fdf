/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:58:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 12:24:41 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * combines the different rgba values into one single int32_t value that is
 * used to draw the pixel on the image
*/
static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * get_light returns the percentage of each RGB color part
*/
static int	get_light(int start, int end, double percent)
{
	return ((int)((1 - percent) * (double)start + percent * (double)end));
}

/**
 * uses rand() to generate random values within the min/max range
*/
int	ft_random(int min, int max)
{
	return (min + rand() / (RAND_MAX / (max - min + 1) + 1));
}

/**
 * @return map->color when map->color_int is false
 * @return interpolated color value
 * percentage: where on the line between start and end is the current pixel
 * get_light returns the percentage of each RGB color part
*/
int	l_clr(t_point *st, t_point *end, t_bresenham *l, t_map *map)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (!map->clr_int)
		return (map->color);
	if (abs(l->dx) > abs(l->dy))
		percentage = (double)(abs((int)l->x - (int)end->x))
			/ (double)(abs((int)l->dx));
	else
		percentage = (double)(abs((int)l->y - (int)end->y))
			/ (double)(abs((int)l->dy));
	percentage = 1 - percentage;
	red = get_light((st->color >> 24) & 0xFF, (end->color >> 24) & 0xFF,
			percentage);
	green = get_light((st->color >> 16) & 0xFF, (end->color >> 16) & 0xFF,
			percentage);
	blue = get_light((st->color >> 8) & 0xFF, (end->color >> 8) & 0xFF,
			percentage);
	return (get_rgba(red, green, blue, 255));
}
