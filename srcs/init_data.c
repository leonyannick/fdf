/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:55:09 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/16 10:23:45 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_data	*init_data(t_data *data, char	*map_file)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("data alloc failed"), NULL);
	data->input = init_input(data->input, map_file);
	if (!data->input)
		return (perror("data->input init failed"), NULL);
	data->map = init_map(data, map_file);
	if (!data->map)
		return (perror("data->map init failed"), NULL);
	data->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!data->mlx)
		return (perror("data->mlx init failed"), NULL);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		return (perror("data->img init failed"), NULL);
	return (data);
}

t_input	*init_input(t_input *input, char *map_file)
{
	input = malloc(sizeof(t_input));
	if (!input)
		return (perror("input alloc failed"), NULL);
	input->map_file = ft_strdup(map_file);
	input->x = 0;
	input->y = 0;
	input->fd = open(map_file, O_RDONLY);
	if (!input->fd)
		return (NULL);
	return (input);
}

t_map	*init_map(t_data *data, char *map_file)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (perror("map alloc failed"), NULL);
	data->map->zoom = ZOOM;
	data->map->xoff = XOFF;
	data->map->yoff = YOFF;
	data->map->xdeg = XDEG;
	data->map->ydeg = YDEG;
	data->map->zdeg = ZDEG;
	data->map->nrows = 0;
	data->map->nclmns = 0;
	data->map->color = P_COLOR;
	data->map->clr_int = false;
	data->map = malloc_map_rows(data->map, data->input);
	data->map = parse_map(data->map, data->input);
	return (data->map);
}
