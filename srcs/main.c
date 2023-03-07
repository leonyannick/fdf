/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/07 12:11:22 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_map(t_map *map)
{
	int	row;
	int	clmn;

	if (map)
	{
		row = 0;
		while ((map->map)[row])
		{
			clmn = 0;
			while ((map->map)[row][clmn])
			{
				free((map->map)[row][clmn]);
				clmn++;
			}
			free((map->map)[row]);
			row++;
		}
	}
	free(map->map);
	free(map);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_map	*map;

	if (argc != 2)
		return (ft_printf("Usage: ./fdf [mapfile] [options]\n"), EXIT_SUCCESS);

/* 	map = init_map(map, argv[1]);
	if (!map)
		return (free_map(map), perror("map init/parsing failed"), EXIT_FAILURE);

	free_map(map); */
	fd = open(argv[1], O_RDONLY);

	free(get_next_line(fd));

	
	/* print_map(map);

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
		return (-1);

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, 512, 512);
	if (!img)
		return (-1);

	
	connect_the_dots(map, img);

	
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (-1);

	mlx_loop(mlx);

	mlx_terminate(mlx);
 */
	
	return (EXIT_SUCCESS);
}
