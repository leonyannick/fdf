/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/14 17:07:08 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_printf("Usage: ./fdf [mapfile] [options]\n"), EXIT_SUCCESS);
	data = init_data(data, argv[1]);
	if (!data)
		return (perror("data init failed"), EXIT_FAILURE);
	paint_pixels(data, project_point);
	// mlx_key_hook(data->mlx, &my_keyhook, data);
	// mlx_loop(data->mlx);
	// mlx_terminate(data->mlx);
	free_map(data->map);
	free(data);
	return (EXIT_SUCCESS);
}
