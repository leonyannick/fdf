/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:03:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/13 19:22:33 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	translate(keys_t key, t_data *data)
{
	data->map->xoff = 0;
	data->map->yoff = 0;
	if (key == MLX_KEY_LEFT)
		data->map->xoff = -S_XOFF;
	if (key == MLX_KEY_RIGHT)
		data->map->xoff = S_XOFF;
	if (key == MLX_KEY_UP)
		data->map->yoff = -S_YOFF;
	if (key == MLX_KEY_DOWN)
		data->map->yoff = S_YOFF;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * BPP);
	paint_pixels(data, &translate_point);
}

static void	zoom(keys_t key, t_data *data)
{
	data->map->zoom = 0;
	if (key == MLX_KEY_EQUAL)
		data->map->zoom = 1;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * BPP);
	paint_pixels(data, &zoom_point);
}

static void	rotate(keys_t key, t_data *data)
{
	data->map->xdeg = 0;
	data->map->ydeg = 0;
	if (key == MLX_KEY_Q)
	{
		xdegree += S_XDEG;
		data->map->xdeg = S_XDEG;
	}
	if (key == MLX_KEY_W)
	{
		xdegree -= S_XDEG;
		data->map->xdeg = -S_XDEG;
	}
	if (key == MLX_KEY_A)
	{
		data->map->ydeg = S_YDEG;
		ydegree += S_YDEG;
	}	
	if (key == MLX_KEY_S)
	{
		ydegree -= S_YDEG;
		data->map->ydeg = -S_YDEG;
	}
	printf ("xdeg:%i ydeg:%i\n", xdegree, ydegree);
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * BPP);
	paint_pixels(data, &project_point);
}

static void	toggle_color(t_data *data)
{
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * BPP);
	if (!data->map->clr_int)
	{
		data->map->clr_int = true;
		paint_pixels(data, &random_point_color);
	}
	else
	{
		data->map->clr_int = false;
		paint_pixels(data, &point_color);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if ((keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(keydata.key, data);
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT
			|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		translate(keydata.key, data);
	if ((keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		zoom(keydata.key, data);
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		toggle_color(data);
}
