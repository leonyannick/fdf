/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:03:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/16 18:13:01 by lbaumann         ###   ########.fr       */
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
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * SZ);
	paint_pixels(data, &translate_point);
}

static void	zoom(keys_t key, t_data *data)
{
	if (key == MLX_KEY_EQUAL)
		data->map->zoom = 1;
	if (key == MLX_KEY_MINUS)
		data->map->zoom = 0;
	paint_pixels(data, &zoom_point);
}

static void	rotate(keys_t key, t_data *data)
{
	data->map->xdeg = 0;
	data->map->ydeg = 0;
	data->map->zdeg = 0;
	if (key == MLX_KEY_Q)
		data->map->xdeg = S_XDEG;
	if (key == MLX_KEY_W)
		data->map->xdeg = -S_XDEG;
	if (key == MLX_KEY_A)
		data->map->ydeg = S_YDEG;
	if (key == MLX_KEY_S)
		data->map->ydeg = -S_YDEG;
	if (key == MLX_KEY_Z)
		data->map->zdeg = S_ZDEG;
	if (key == MLX_KEY_X)
		data->map->zdeg = -S_ZDEG;
	paint_pixels(data, &project_point);
}

static void	toggle_color(t_data *data)
{
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

void	backview(t_data *data)
{
	paint_pixels(data, &reset);
	data->map->xdeg = 90;
	data->map->ydeg = 180;
	data->map->zdeg = 180;
	paint_pixels(data, &project_point);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if ((keydata.key == MLX_KEY_Q || keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_Z || keydata.key == MLX_KEY_X)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(keydata.key, data);
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT
			|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		translate(keydata.key, data);
	if ((keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		zoom(keydata.key, data);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		toggle_color(data);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		paint_pixels(data, &reset);
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		backview(data);
}
