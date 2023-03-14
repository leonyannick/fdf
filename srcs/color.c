/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:58:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/14 17:09:42 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	get_light(int start, int end, double percent)
{
	return ((int)((1 - percent) * (double)start + percent * (double)end));
}

int	ft_random(int min, int max)
{
	return (min + rand() / (RAND_MAX / (max - min + 1) + 1));
}

int	line_clr_inter(t_point *st, t_point *end, t_bresenham *l, t_map *map)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (!map->clr_int)
		return (map->color);
	if (abs(l->dx) > abs(l->dy))
		percentage = (double)(abs((int)l->x - (int)end->x)) / (double)(abs((int)l->dx));
	else
		percentage = (double)(abs((int)l->y - (int)end->y)) / (double)(abs((int)l->dy));
	percentage = 1 - percentage;
	red = get_light((st->color >> 24) & 0xFF, (end->color >> 24) & 0xFF,
			percentage);
	green = get_light((st->color >> 16) & 0xFF, (end->color >> 16) & 0xFF,
			percentage);
	blue = get_light((st->color >> 8) & 0xFF, (end->color >> 8) & 0xFF,
			percentage);
	return (get_rgba(red, green, blue, 255));
}
