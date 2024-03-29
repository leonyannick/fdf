/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:55:09 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/20 13:07:10 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/**
 * allocates memory for input struct. saves name on map file and opens map
 * file
 * @return NULL on error, pointer to input struct in success
*/
static t_input	*init_input(t_input *input, char *map_file)
{
	input = malloc(sizeof(t_input));
	if (!input)
		return (perror("input alloc failed"), NULL);
	input->map_file = ft_strdup(map_file);
	input->x = 0;
	input->y = 0;
	input->fd = open(map_file, O_RDONLY);
	if (input->fd < 0)
		return (free(input->map_file), free(input), NULL);
	return (input);
}

/**
 * allocs memory for map struct. initializes map attributes. calls
 * malloc_map_rows function to allocates space for map. parse map 
 * parses map file and fills map struct with data
*/
static t_map	*init_map(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (perror("map alloc failed"), NULL);
	data->map->zoom = 0;
	data->map->xoff = 0;
	data->map->yoff = 0;
	data->map->xdeg = XDEG;
	data->map->ydeg = YDEG;
	data->map->zdeg = 0;
	data->map->nrows = 0;
	data->map->nclmns = 0;
	data->map->color = P_COLOR;
	data->map->clr_int = false;
	data->map = malloc_map_rows(data->map, data->input, data);
	data->map = parse_map(data->map, data->input, data);
	return (data->map);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		data->map = free_map(data->map, data->input->y);
	if (data->input)
	{
		data->input->map_file = ft_free_set_null(data->input->map_file);
		data->input->line = ft_free_set_null(data->input->line);
		data->input->split_line = free_split_arr(data->input->split_line);
		data->input = ft_free_set_null(data->input);
	}
}

/**
 * allocates memory for data struct and calls other functions to initialize
 * input struct, map struct, mlx and mlx image
 * @return NULL in case of error, pointer to data struct on success
*/
t_data	*init_data(t_data *data, char	*map_file)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("data alloc failed"), NULL);
	data->input = init_input(data->input, map_file);
	if (!data->input)
		return (perror("data->input init failed"), free(data), NULL);
	data->map = init_map(data);
	if (!data->map)
		return (perror("data->map init failed"),
			free_data(data), free(data), NULL);
	data->mlx = mlx_init(WIDTH, HEIGHT, "fdf", true);
	if (!data->mlx)
		return (perror("data->mlx init failed"),
			free_data(data), free(data), NULL);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		return (perror("data->img init failed"),
			free_data(data), free(data), NULL);
	return (data);
}
