/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:23:20 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 10:34:26 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * connects all points in the grid. first each point is connected with the next
 * point in its row. after that, each point is connected with its vertical
 * next neighbour in the same column
*/
void	connect_the_dots(t_data *data)
{
	int		r;
	int		c;

	r = -1;
	while (++r < data->map->nrows)
	{
		c = -1;
		while (++c < (data->map->nclmns - 1))
		{
			plot_line((data->map->map_arr)[r][c],
				(data->map->map_arr)[r][c + 1], data);
		}
	}
	c = -1;
	while (++c < data->map->nclmns)
	{
		r = -1;
		while (++r < (data->map->nrows - 1))
			plot_line((data->map->map_arr)[r][c],
				(data->map->map_arr)[r + 1][c], data);
	}
}

/**
 * goes through map_arr and applies the function f to each point
 * after having applied the function it connects all points again,
 * which actually puts the pixels on the image
*/
t_data	*paint_pixels(t_data *data, void *(*f)(t_point *point, t_map *map))
{
	int		row;
	int		clmn;

	row = 0;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * SZ);
	while (row < data->map->nrows)
	{
		clmn = 0;
		while (clmn < (data->map->nclmns))
		{
			if (!(*f)((data->map->map_arr)[row][clmn], data->map))
				return (NULL);
			clmn++;
		}
		row++;
	}
	connect_the_dots(data);
	return (data);
}
