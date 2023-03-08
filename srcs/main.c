/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/08 15:57:10 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_map(t_map *map)
{
	int	row;
	int	clmn;

	if (!map && !(map->map))
		return ;
	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < map->nclmns)
		{
			free((map->map)[row][clmn]);
			clmn++;
		}
		free((map->map)[row]);
		row++;
	}
	free(map->map);
	free(map);
}

t_input	*init_input(t_input *input, char *map_name)
{
	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->x = 0;
	input->y = 0;
	input->fd = open(map_name, O_RDONLY);
	if (!input->fd)
		return (NULL);
	return (input);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_map	*map;
	t_input	*input;

	if (argc != 2)
		return (ft_printf("Usage: ./fdf [mapfile] [options]\n"), EXIT_SUCCESS);
	input = init_input(input, argv[1]);
	if (!input)
		return (perror("input init/parsing failed"), EXIT_FAILURE);
	map = init_map(map, input, argv[1]);
	if (!map)
		return (free_map(map), perror("map init/parsing failed"), EXIT_FAILURE);
	map = init_window(map);
	if (!map)
		return (free_map(map), perror("mlx window init failed"), EXIT_FAILURE);
	
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) < 0)
		return (EXIT_FAILURE);
	map = change_points(map, project_point);


	mlx_key_hook(map->mlx, &my_keyhook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	
	free_map(map);
	return (EXIT_SUCCESS);
}
