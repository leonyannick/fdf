/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:03:34 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 10:16:08 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * mlx function for working with keyhooks. for each set of keys the respective
 * function from key_backend is called to process the actual key input and
 * actually display the change to the image
*/
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
