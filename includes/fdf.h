/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/05 17:55:33 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

//mlx window size
# define WIDTH 512
# define HEIGHT 512

//f(rad) = rad * (180 / pi)
# define RAD2DEG 57.295779513082323
//f(deg) = deg * (pi / 180)
# define DEG2RAD 0.017453292519943

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	struct s_point	*next;
}t_point;

typedef struct s_pointd
{
	double				x;
	double				y;
	double				z;
}t_pointd;

typedef struct s_map
{
	t_point		**map;
	int			nrows;
	int			nclmns;
}t_map;


/**
 * Struct to store necessary values for Bresenham algorithm
 * @param x x value of pixel that is drawn. initialized to start point
 * @param y x value of pixel that is drawn. initialized to start point
 * @param err error of diagonal pixel
 * @param e2 error of diagonal pixel precomputed
 * @param sx step in x direction. 1 if x2 > x1, else -1
 * @param sy step in y direction. 1 if y2 > y1, else -1
 * @param dy -abs(y2-y1) -> always negative
 * @param dx abs(x2-x1) -> always positive
*/
typedef struct s_bresenham
{
	int		x;
	int		y;
	int		err;
	int		e2;
	int		sx;
	int		sy;
	int		dy;
	int		dx;
}t_bresenham;

//line plotting
void	plot_line(t_point *p1, t_point *p2, mlx_image_t *img);

//map parsing
t_map	*parse_map(int fd);
t_map	*add_point(t_map *map, int x, int y, int z);
void	print_map(t_map *map);

//isometric projection
t_point	*isometric_proj(t_point *point);

#endif
