/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/17 14:56:49 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		if (data->input->map_file)
		free(data->input->map_file);
		if (data->input->line)
			free(data->input->line);
		if (data->input->split_line)
			free_split_arr(data->input->split_line);
		free(data->input);
	}
	if (data->map)
		free_map(data->map);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		return (ft_printf("Usage: ./fdf [mapfile]\n"), EXIT_SUCCESS);
	data = init_data(data, argv[1]);
	if (!data)
		return (perror("data init failed"), free_data(data), EXIT_FAILURE);
	paint_pixels(data, &project_point);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_map(data->map);
	free(data);
	return (EXIT_SUCCESS);
}
