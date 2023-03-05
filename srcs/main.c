/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/05 12:26:59 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_p(t_point *point)
{
	printf("x: %i\n", point->x);
	printf("y: %i\n", point->y);
	printf("z: %i\n", point->z);
	printf("\n");
}

int	main(int argc, char **argv)
{
	/* int	fd;
	t_map	*map;

	if (argc != 2)
		return (ft_printf("Usage: ./fdf [mapfile] [options]\n"), EXIT_SUCCESS);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	map = parse_map(fd);
	// print_map(map);

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
		return (-1);

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, 512, 512);
	if (!img)
		return (-1);

	t_point *p1 = malloc(sizeof(t_point));
	t_point *p2 = malloc(sizeof(t_point));
	p1->x = 10;
	p1->y = 10;
	p2->x = 300;
	p2->y = 200;
	
	plot_line(p1, p2, img);

	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (-1);

	mlx_loop(mlx);

	mlx_terminate(mlx); */

	
	return (EXIT_SUCCESS);
}
