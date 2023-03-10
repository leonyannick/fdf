/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:58:03 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/09 18:36:22 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int ft_random(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_point	*random_point_color(t_point *point, t_map *map)
{
	point->color = ft_random(0xFF000000, 0x00FF0000);
	return (point);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * (double)start + percentage * (double)end));
}

int	line_color_inter(t_point *start, t_point *end, t_bresenham *line, t_map *map)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (!map->clr_int)
		return (0xFFFFFFFF);
	if (abs(line->dx) > abs(line->dy))
		percentage = (double)(abs(line->x - end->x)) / (double)(abs(line->dx));
	else
		percentage = (double)(abs(line->y - end->y)) / (double)(abs(line->dy));
	percentage = 1 - percentage;
	
	red = get_light((start->color >> 24) & 0xFF, (end->color >> 24) & 0xFF, percentage);
	green = get_light((start->color >> 16) & 0xFF, (end->color >> 16) & 0xFF, percentage);
	blue = get_light((start->color >> 8) & 0xFF, (end->color >> 8) & 0xFF, percentage);
	return (get_rgba(red, green, blue, 255));
}

void	toggle_color(t_map *map)
{
	if (map->clr_int)
		map->clr_int = false;
	else
		map->clr_int = true;
	ft_memset(map->img->pixels, 0, map->img->width * map->img->height * BPP);
	change_points(map, &random_point_color);
	connect_the_dots(map);
}

