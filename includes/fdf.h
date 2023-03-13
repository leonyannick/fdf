/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:42:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/13 19:23:48 by lbaumann         ###   ########.fr       */
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
# include <stdbool.h>

//mlx window size
# define WIDTH 1920
# define HEIGHT 1080

//deg = rad * (180 / pi)
# define RAD2DEG 57.295779513082323
//rad = deg * (pi / 180)
# define DEG2RAD 0.017453292519943

//initial map attributes (isometric proj)
# define ZOOM 10
# define YOFF 100
# define XOFF 100
# define XDEG 0
# define YDEG 0
# define P_COLOR 0xFFFFFFFF

//step size for key presses
# define S_ZOOM 1.1
# define S_YOFF 10
# define S_XOFF 10
# define S_XDEG 5
# define S_YDEG 5

#define BPP sizeof(int32_t)

int xdegree;
int ydegree;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}t_point;

typedef struct s_pointd
{
	double				x;
	double				y;
	double				z;
}t_pointd;

typedef struct s_map
{
	t_point		***map_arr;
	int			nrows;
	int			nclmns;
	float		zoom;
	int			yoff;
	int			xoff;
	int			xdeg;
	int			ydeg;
	int			color;
	bool		clr_int;
}t_map;

typedef struct s_input
{
	char	*map_file;
	char	*line;
	char	**split_line;
	int		x;
	int		y;
	int		fd;
}t_input;

typedef struct s_data
{
	t_map		*map;
	mlx_t*		mlx;
	mlx_image_t	*img;
	t_input		*input;
}t_data;

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
	int		clr_step;
}t_bresenham;

//init_data
t_data		*init_data(t_data *data, char	*map_file);
t_input		*init_input(t_input *input, char *map_file);
t_map		*init_map(t_data *data, char *map_file);

//line plotting
void		plot_line(t_point *p1, t_point *p2, t_data *data);
void		connect_the_dots(t_data *data);

//map
t_map		*malloc_map_rows(t_map *map, t_input *input);
t_map		*parse_map(t_map *map, t_input *input);
t_map		*add_point(t_map *map, int x, int y, int z);

//utils
void		print_map(t_map *map);
void		free_split_arr(char **arr);
int			n_sub_arr(char **s);
t_input		*gnl_split(t_input *input);

//point operations
t_data	*paint_pixels(t_data *data, t_point *(*f)(t_point *point, t_map *map));
t_point		*translate_point(t_point *point, t_map *map);
t_point		*project_point(t_point *point, t_map *map);
t_point		*zoom_point(t_point *point, t_map *map);
t_point	*random_point_color(t_point *point, t_map *map);
t_point	*point_color(t_point *point, t_map *map);

//window stuff
void	my_keyhook(mlx_key_data_t keydata, void* param);

//projection
t_pointd	*rotate_yaxis(t_pointd *point, double rad);
t_pointd	*rotate_xaxis(t_pointd *point, double rad);
t_pointd	*vec_mat_mul(t_pointd *p, const double m[3][3]);

//color
int	line_color_inter(t_point *start, t_point *end, t_bresenham *line, t_map *map);
int ft_random(int min, int max);

//main
t_input	*init_input(t_input *input, char *map_name);

#endif
