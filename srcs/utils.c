/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:22:54 by lbaumann          #+#    #+#             */
/*   Updated: 2023/03/10 11:23:07 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_map(t_map *map)
{
	int		row;
	int		clmn;
	t_point	*pt;

	row = 0;
	while (row < map->nrows)
	{
		clmn = 0;
		while (clmn < map->nclmns)
		{
			pt = (map->map)[row][clmn];
			printf("(%i,%i)\033[35;1m%i\033[0m\t", pt->x, pt->y, pt->z);
			clmn++;
		}
		printf("\n");
		row++;
	}
}
