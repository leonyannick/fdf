/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/14 14:50:16 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_map(t_map *map)
{
	int	row;
	int	clmn;

	if (!map && !(map->map_arr))
		return ;
	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < map->nclmns)
		{
			free((map->map_arr)[row][clmn]);
			clmn++;
		}
		free((map->map_arr)[row]);
		row++;
	}
	free(map->map_arr);
	free(map);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_printf("Usage: ./fdf [mapfile] [options]\n"), EXIT_SUCCESS);
	data = init_data(data, argv[1]);
	if (!data)
		return (perror("data init failed"), EXIT_FAILURE);
	
	paint_pixels(data, project_point);

	/* t_point *p1 = malloc(sizeof(t_point));
	t_point *p2 = malloc(sizeof(t_point));

	p1->x = 60;
	p1->y = 60;
	p1->z = 0;
	p1->color = 0xFF0000FF;

	p2->x = 500;
	p2->y = 500;
	p2->z = 0;
	p2->color = 0x00FF00FF;
	map->clr_int = true;
	plot_line(p2, p1, map); */

	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free_map(data->map);
	free(data);
	return (EXIT_SUCCESS);
}
