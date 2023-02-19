/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:52:40 by lbaumann          #+#    #+#             */
/*   Updated: 2023/02/19 12:13:17 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (ft_printf("Program takes exactly one argument!\n"), EXIT_SUCCESS);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error"), EXIT_FAILURE);
	ft_printf("%s", get_next_line(fd));
	
	
	return (EXIT_SUCCESS);
}
