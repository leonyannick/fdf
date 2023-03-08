/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:03:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/08 17:44:13 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_map	*init_window(t_map *map)
{
	map->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!map->mlx)
		return (NULL);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
		return (NULL);
	return (map);
}

static void	translate(keys_t key, t_map *map)
{
	map->xoff = 0;
	map->yoff = 0;
	if (key == MLX_KEY_LEFT)
		map->xoff = -S_XOFF;
	if (key == MLX_KEY_RIGHT)
		map->xoff = S_XOFF;
	if (key == MLX_KEY_UP)
		map->yoff = -S_YOFF;
	if (key == MLX_KEY_DOWN)
		map->yoff = S_YOFF;
	ft_memset(map->img->pixels, 0, map->img->width * map->img->height * BPP);
	map = change_points(map, &translate_point);
}

static void	zoom(keys_t key, t_map *map)
{
	map->zoom = 0;
	if (key == MLX_KEY_EQUAL)
		map->zoom = 1;
	ft_memset(map->img->pixels, 0, map->img->width * map->img->height * BPP);
	map = change_points(map, &zoom_point);
}

static void	rotate(keys_t key, t_map *map)
{
	map->xdeg = 0;
	map->ydeg = 0;
	if (key == MLX_KEY_Q)
		map->xdeg = S_XDEG;
	if (key == MLX_KEY_W)
		map->xdeg = -S_XDEG;
	if (key == MLX_KEY_A)
		map->ydeg = S_YDEG;
	if (key == MLX_KEY_S)
		map->ydeg = -S_YDEG;
	ft_memset(map->img->pixels, 0, map->img->width * map->img->height * BPP);
	map = change_points(map, &project_point);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if ((keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(keydata.key, map);
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT
			|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		translate(keydata.key, map);
	if ((keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		zoom(keydata.key, map);
}
