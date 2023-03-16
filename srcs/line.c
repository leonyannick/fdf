/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:26:05 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/16 17:52:55 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * Mallocs memory for Bresenham struct and assigns all the values necessary
 * for the Bresenham line algorithm
 * @param p1 starting point p1(x1,y1)
 * @param p2 end point p2(x2,y2)
 * @param line pointer to Bresenham struct
 * @return NULL if allocations fails OR pointer to allocated Bresenham struct
*/
static t_bresenham	*init_line(t_point *p1, t_point *p2, t_bresenham *line)
{
	line = malloc(sizeof(t_bresenham));
	if (!line)
		return (NULL);
	line->dx = abs((int)p2->x - (int)p1->x);
	line->dy = -abs((int)p2->y - (int)p1->y);
	line->err = line->dx + line->dy;
	line->x = (int)p1->x;
	line->y = (int)p1->y;
	if (p1->x > p2->x)
		line->sx = -1;
	else
		line->sx = 1;
	if (p1->y > p2->y)
		line->sy = -1;
	else
		line->sy = 1;
	return (line);
}

/**
 * Draws a line on the mlx_image from p1 to p2. First Bresenham struct
 * is assigned via init_line function (freed in the end of function).
 * Positive error value indicates deviation to implicit function to one
 * side, negative to the other side. There are always three possible
 * candidates for the next pixel: (x+1)(y), (x)(y+1), (x+1)(y+1).
 * Error value is always precomputed (one diagonal pixel ahead). It is
 * assumed that this diagonal pixel (x+1)(y+1) is set next. x and y
 * are adjusted by the step direction (sx, sy) if the diagonal pixel is the 
 * right candidate (via the two if statements).
 * @param p1 starting point p1(x1,y1)
 * @param p2 end point p2(x2,y2) 
 * @param img mlx_image
*/
void	plot_line(t_point *p1, t_point *p2, t_data *data)
{
	t_bresenham	*l;

	l = init_line(p1, p2, l);
	if (!l)
		return ;
	while (l->x != (int)p2->x || l->y != (int)p2->y)
	{
		if ((l->x >= 0) && (l->y >= 0) && (l->x < WIDTH) && (l->y < HEIGHT))
			mlx_put_pixel(data->img, l->x, l->y,
				line_clr_inter(p1, p2, l, data->map));
		l->e2 = 2 * l->err;
		if (l->e2 >= l->dy)
		{
			l->err += l->dy;
			l->x += l->sx;
		}
		if (l->e2 <= l->dx)
		{
			l->err += l->dx;
			l->y += l->sy;
		}
	}
	if ((l->x >= 0) && (l->y >= 0) && (l->x < WIDTH) && (l->y < HEIGHT))
		mlx_put_pixel(data->img, l->x, l->y, p2->color);
	free(l);
}

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
