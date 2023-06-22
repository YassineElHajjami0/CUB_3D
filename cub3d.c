/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:52:44 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/22 16:30:08 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

int	ft_exit(void)
{
	exit(0);
}

int	loop(t_all *all)
{
	mlx_put_image_to_window(all->mlx, all->win, all->data.img, 0, 0);
	update_coordination(all);
	set_rays(all);
	draw_ceil(all);
	rendering_walls(all);
	draw_floor(all);
	draw_mini_map(all);
	return (0);
}

t_info	*get_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(1);
	info->ceil[0] = -1;
	info->ceil[1] = -1;
	info->ceil[2] = -1;
	info->floor[0] = -1;
	info->floor[1] = -1;
	info->floor[2] = -1;
	info->north = NULL;
	info->south = NULL;
	info->east = NULL;
	info->west = NULL;
	return (info);
}

int	check_extension(char *s)
{
	if (ft_strlen(s) >= 5 &&
	     s[ft_strlen(s) - 1] == 'b' && s[ft_strlen(s) - 2] == 'u'
	    && s[ft_strlen(s) - 3] == 'c' && s[ft_strlen(s) - 4] == '.'
	    && s[ft_strlen(s) - 5] != '/')
	    return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	*all;
	int		fd;

	if (ac != 2 || !check_extension(av[1]))
		write_error(2);

	all = malloc(sizeof(t_all));
	all->info = get_info();
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		write_error(2);
	if (!parse_option(fd, all->info))
		write_error(2);
	all->choosed_map = av[1];
	parsing(fd, all);
	close(fd);
	init_all(all, all->info);
	init_player(all);
	mlx_hook(all->win, 2, 0, key_hook, all);
	mlx_hook(all->win, 3, 0, key_released, all);
	mlx_hook(all->win, 17, 0, &ft_exit, NULL);
	mlx_loop_hook(all->mlx, loop, all);
	mlx_loop(all->mlx);
	return (0);
}

/*
	1 		----> 	100 000
	line	----> 	height
*/