/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:52:44 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/16 12:12:37 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

int	key_hook(int key, t_all *all)
{
	if (key == W)
		all->player->walk_direction = 1;
	else if (key == S)
		all->player->walk_direction = -1;
	else if (key == A)
	{
		all->player->flag = 1;
		all->player->walk_direction = 1;
	}
	else if (key == D)
	{
		all->player->flag = -1;
		all->player->walk_direction = 1;
	}
	else if (key == RIGHT)
		all->player->turn_direction = 1;
	else if (key == LEFT)
		all->player->turn_direction = -1;


	else if (key == 53)
		exit(0);
	return (0);
}

int	key_released(int keycode, t_all *all)
{   
	(void)keycode;
	all->player->turn_direction = 0;
	all->player->walk_direction = 0;
	all->player->flag = 0;
	return (0);
}

int	ft_exit(void)
{
	exit(0);
}

// unsigned int	*get_direction(t_all *all, int column)
// {
// 	if (all->rays[column].facing_up)
// 	{
// 		if (!all->rays[column].hitvertical)
// 			return all->north_array;
// 		if (all->rays[column].facing_right)
// 			return all->west_array;
// 		return all->east_array;
// 	}
// 	else
// 	{
// 		if (!all->rays[column].hitvertical)
// 			return all->south_array;
// 		if (all->rays[column].facing_right)
// 			return all->east_array;
// 		return all->west_array;
// 	}
// }

unsigned int *get_direction(t_all *all, int column)
{
	if (all->rays[column].ray_angle >= M_PI && all->rays[column].ray_angle <= 2 * M_PI)
	{
		//north west east
		if (!all->rays[column].hitvertical)
		{
			return (all->north_array);//north white
		}
		if (all->rays[column].facing_right)
			return (all->east_array);//east dark
		return (all->west_array);//west red
	}
	else 
	{
		if (!all->rays[column].hitvertical)
			return (all->south_array);//south move
		if (all->rays[column].facing_right)
			return (all->east_array);//east dark
		return (all->west_array);//west red
	}
}

void	draw_column(t_all *all, int column, int start, int end)
{
	double	offset;
	int		i;
	double	line;
	unsigned int *direction;

	if (all->rays[column].hitvertical)
		offset = fmod(all->rays[column].coor.y , 64);
	else
		offset = fmod(all->rays[column].coor.x , 64);
	direction = get_direction(all, column);
	i = start;
	while (i < end)
	{	
		line = (i - start) * 64 / all->rays[column].column_height;
		my_mlx_pixel_put(all, column,i, direction[(int)offset + (64 * (int)line)]);
		// my_mlx_pixel_put(all, column,i, direction);
		i++;
	}
}
 

void	rendering_walls(t_all *all)
{
	int half_screen = WINDOW_HEIGHT / 2;

	all->i = -1;
	while (++all->i < NUMBER_RAYS)
	{
		draw_column(all, all->i, half_screen - all->rays[all->i].column_height / 2, half_screen + all->rays[all->i].column_height / 2);
	}
}

void	draw_floor(t_all *all)
{
	double	start;
	int i = -1;

	while (++i < NUMBER_RAYS)
	{
		start = WINDOW_HEIGHT / 2 + all->rays[i].column_height / 2;
		while (start <= WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(all, i, start, 0x55165E);
			start++;
		}
	}
}

void	draw_ceil(t_all *all)
{
	double	start;
	int i = -1;

	while (++i < NUMBER_RAYS)
	{
		start = 0;
		while (start <= WINDOW_HEIGHT / 2 - all->rays[all->i].column_height / 2)
		{
			my_mlx_pixel_put(all, i, start, 0x06265C);
			start++;
		}
	}
}

int	loop(t_all *all)
{
	mlx_put_image_to_window(all->mlx, all->win, all->data.img, 0, 0); 
	// clear_image(all);
	update_coordination(all);
	set_rays(all);
	draw_ceil(all);   
	rendering_walls(all);
	draw_floor(all);
	draw_mini_map(all);
	return (0);
}

t_info	*get_info()
{
	t_info *info = malloc(sizeof(t_info));
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

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	t_all	*all;
	t_info *info;
	int		fd;

//.ber

	info = get_info();
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		write_error(2);
	//parsing

	if (!parse_option(fd, info))
		write_error(2);
	//launching the game 

	all = malloc(sizeof(t_all));
	all->choosed_map = av[1];
	// parsing(ac, av, all);

	parsing(fd, all);
	close(fd);
	init_all(all, info);
	init_player(all);
	mlx_hook(all->win, 2, 0, key_hook, all);
	mlx_hook(all->win, 3, 0, key_released, all);
	mlx_hook(all->win, 17, 0, &ft_exit, NULL);
	mlx_loop_hook(all->mlx, loop, all);
	mlx_loop(all->mlx);
	return (0);
}
