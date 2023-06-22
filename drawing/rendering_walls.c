/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:12:25 by amentag           #+#    #+#             */
/*   Updated: 2023/06/22 14:50:07 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	*get_direction(t_all *all, int column)
{
	if (all->rays[column].ray_angle >= M_PI \
		&& all->rays[column].ray_angle <= 2 * M_PI)
	{
		if (!all->rays[column].hitvertical)
		{
			return (all->north_array);
		}
		if (all->rays[column].facing_right)
			return (all->east_array);
		return (all->west_array);
	}
	else
	{
		if (!all->rays[column].hitvertical)
			return (all->south_array);
		if (all->rays[column].facing_right)
			return (all->east_array);
		return (all->west_array);
	}
}

void	draw_column(t_all *all, int column, int start, int end)
{
	double			offset;
	int				i;
	double			line;
	unsigned int	*direction;

	if (all->rays[column].hitvertical)
		offset = fmod(all->rays[column].coor.y, 64);
	else
		offset = fmod(all->rays[column].coor.x, 64);
	direction = get_direction(all, column);
	i = start;
	while (i < end)
	{	
		line = (i - start) * 64 / all->rays[column].column_height;
		my_mlx_pixel_put(all, column, i, \
			direction[(int)offset + (64 * (int)line)]);
		i++;
	}
}

void	rendering_walls(t_all *all)
{
	int	half_screen;

	half_screen = WINDOW_HEIGHT / 2;
	all->i = -1;
	while (++all->i < NUMBER_RAYS)
	{
		draw_column(all, all->i, \
		half_screen - all->rays[all->i].column_height / 2, \
		half_screen + all->rays[all->i].column_height / 2);
	}
}

void	draw_floor(t_all *all)
{
	double	start;
	int		i;

	i = -1;
	while (++i < NUMBER_RAYS)
	{
		start = WINDOW_HEIGHT / 2 + all->rays[i].column_height / 2;
		while (start <= WINDOW_HEIGHT)
		{
			// my_mlx_pixel_put(all, i, start, 0x55165E);
			my_mlx_pixel_put(all, i, start, (all->info->floor[0] << 16) + (all->info->floor[1] << 8) + all->info->floor[2]);
			start++;
		}
	}
}

void	draw_ceil(t_all *all)
{
	double	start;
	int		i;

	i = -1;
	while (++i < NUMBER_RAYS)
	{
		start = 0;
		while (start <= WINDOW_HEIGHT / 2 - all->rays[all->i].column_height / 2)
		{
			my_mlx_pixel_put(all, i, start, (all->info->ceil[0] << 16) + (all->info->ceil[1] << 8) + all->info->ceil[2]);
			// my_mlx_pixel_put(all, i, start, 0x06265C);
			start++;
		}
	}
}
