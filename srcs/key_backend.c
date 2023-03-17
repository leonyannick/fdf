/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_backend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:16:37 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 10:23:20 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * object is can be moved arount with arrow keys
*/
void	translate(keys_t key, t_data *data)
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
	paint_pixels(data, &translate_point);
}

/**
 * enlarges/shrinks object
 * equals/plus-key[+]
 * minus-key[-]
*/
void	zoom(keys_t key, t_data *data)
{
	if (key == MLX_KEY_EQUAL)
		data->map->zoom = 1;
	if (key == MLX_KEY_MINUS)
		data->map->zoom = 0;
	paint_pixels(data, &zoom_point);
}

/**
 * rotates the object around its different axis by step size
 * saved in macros in header file
 * x axis: Q[+] W[-]
 * y axis: A[+] S[-]
 * z axis: Z[+] X[-]
*/
void	rotate(keys_t key, t_data *data)
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

/**
 * when key c is pressed ittoggles between assigning each point to a random
 * color and the color value that is stated in the macro in the header file
*/
void	toggle_color(t_data *data)
{
	if (!data->map->clr_int)
	{
		data->map->clr_int = true;
		paint_pixels(data, &random_point_color);
	}
	else
	{
		data->map->clr_int = false;
		connect_the_dots(data);
	}
}

/**
 * resets to the initial values and rotates the object so it can be seen
 * from the back
*/
void	backview(t_data *data)
{
	paint_pixels(data, &reset);
	data->map->xdeg = 90;
	data->map->ydeg = 180;
	data->map->zdeg = 180;
	paint_pixels(data, &project_point);
}
