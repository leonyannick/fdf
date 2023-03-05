/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:26:05 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/05 20:10:48 by lbaumann         ###   ########.fr       */
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
	line->dx = abs(p2->x - p1->x);
	line->dy = -abs(p2->y - p1->y);
	line->err = line->dx + line->dy;
	line->x = p1->x;
	line->y = p1->y;
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
void	plot_line(t_point *p1, t_point *p2, mlx_image_t *img)
{
	t_bresenham	*line;

	line = init_line(p1, p2, line);
	if (!line)
		return ;
	while (line->x != p2->x || line->y != p2->y)
	{
		mlx_put_pixel(img, line->x, line->y, 0xFF00FF);
		line->e2 = 2 * line->err;
		if (line->e2 >= line->dy)
		{
			line->err += line->dy;
			line->x += line->sx;
		}
		if (line->e2 <= line->dx)
		{
			line->err += line->dx;
			line->y += line->sy;
		}
	}
	mlx_put_pixel(img, line->x, line->y, 0xFF00FF);
	free(line);
}

void	connect_the_dots(t_map *map, mlx_image_t *img)
{
	int		row;
	int		clmn;

	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < (map->nclmns))
		{
			(map->map)[row][clmn] = isometric_proj((map->map)[row][clmn]);
			clmn++;
		}
		row++;
	}

	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < (map->nclmns - 1))
		{
			plot_line((map->map)[row][clmn], (map->map)[row][clmn + 1], img);
			clmn++;
		}
		row++;
	}

	clmn = 0;
	while (clmn < map->nclmns)
	{
		row = 0;
		while (row < (map->nrows - 1))
		{
			plot_line((map->map)[row][clmn], (map->map)[row + 1][clmn], img);
			row++;
		}
		clmn++;
	}
	
}
