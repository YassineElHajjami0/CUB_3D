/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:44:35 by amentag           #+#    #+#             */
/*   Updated: 2023/06/23 07:04:03 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line(t_all *all, t_point a, t_point b)
{
	double	delta_y;
	double	delta_x;
	int		steps;
	double	x_step;
	double	y_step;

	a.x = 3 * TILE_SIZE / 2;
	a.y = 3 * TILE_SIZE / 2;
	b.x = 3 * TILE_SIZE / 2 + cos(all->player->rotation_angle) * 40;
	b.y = 3 * TILE_SIZE / 2 + sin(all->player->rotation_angle) * 40;
	delta_y = b.y - a.y;
	delta_x = b.x - a.x;
	if (fabs(delta_x) > fabs(delta_y))
		steps = fabs(delta_x);
	else
		steps = fabs(delta_y);
	x_step = delta_x / steps;
	y_step = delta_y / steps;
	while (steps--)
	{
		my_mlx_pixel_put(all, a.x, a.y, 0x871F78);
		a.x += x_step;
		a.y += y_step;
	}
}

unsigned int	get_color(t_all *all, int x, int y)
{
	double	posx;
	double	posy;

	posx = all->player->coor.x - 3 * TILE_SIZE / 2 + x;
	posy = all->player->coor.y - 3 * TILE_SIZE / 2 + y;
	if (posy / 64 < 0 || posy / 64 >= all->number_lines)
		return (0x4E1852);
	if (posx / 64 < 0 || posx / 64 >= ft_strlen(all->map[(int)(posy / 64)]))
		return (0x4E1852);
	if (all->map[(int)(posy / 64)][(int)(posx / 64)] == '1')
		return (0x4E1852);
	return (0xdfbdff);
}

void	init_points(t_point *a, t_point *b)
{
	a->x = -1;
	a->y = -1;
	b->x = -1;
	b->y = -1;
}

void	draw_mini_map(t_all *all, int i)
{
	int				j;
	unsigned int	color;
	t_point			a;
	t_point			b;

	init_points(&a, &b);
	while (++i < TILE_SIZE * 3)
	{
		j = -1;
		while (++j < TILE_SIZE * 3)
		{
			color = get_color(all, j, i);
			my_mlx_pixel_put(all, j, i, color);
		}
	}
	i = 3 * TILE_SIZE / 2 - 5;
	while (i < 3 * TILE_SIZE / 2 + 5)
	{
		j = 3 * TILE_SIZE / 2 - 5;
		while (j < 3 * TILE_SIZE / 2 + 5)
			my_mlx_pixel_put(all, j++, i, 0x000000);
		i++;
	}
	draw_line(all, a, b);
}
