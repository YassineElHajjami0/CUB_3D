/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_fns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:47:07 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/20 19:05:43 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
		return ;
	dst = all->data.addr + (y * all->data.line_length + x * \
	(all->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

bool	hitted_with_wall(double x, double y, t_all *all)
{
	int	line;
	int	col;

	line = floor(y / 64);
	col = floor(x / 64);
	if (line < 0 || col < 0 || line >= all->number_lines \
		|| col >= (int)ft_strlen(all->map[line]))
		return (true);
	return (all->map[line][col] == '1');
}

void	player_rotation_and_facing(t_all *all, int *step,
	t_point *new_coordination)
{
	double	rotation_angle;

	all->player->rotation_angle += all->player->turn_direction * \
		all->player->rotation_speed;
	if (all->player->rotation_angle > 2 * M_PI)
		all->player->rotation_angle -= 2 * M_PI;
	if (all->player->rotation_angle < 0)
		all->player->rotation_angle += 2 * M_PI;
	rotation_angle = all->player->rotation_angle + \
		(double)all->player->flag * M_PI / 2;
	if (rotation_angle > 2 * M_PI)
		rotation_angle -= 2 * M_PI;
	if (rotation_angle < 0)
		rotation_angle += 2 * M_PI;
	*step = all->player->walk_direction * all->player->move_speed;
	new_coordination->x = all->player->coor.x + \
		cos(rotation_angle) * (*step);
	new_coordination->y = all->player->coor.y + \
		sin(rotation_angle) * (*step);
}

void	update_coordination(t_all *all)
{
	int		step;
	t_point	new_coordination;
	int		line;
	int		column;

	player_rotation_and_facing(all, &step, &new_coordination);
	line = (int)(new_coordination.y / 64);
	column = (int)(new_coordination.x / 64);
	if (line >= all->number_lines || column >= (int)ft_strlen(all->map[line]))
		return ;
	if (hitted_with_wall(new_coordination.x, new_coordination.y - 5, all))
		return ;
	if (hitted_with_wall(new_coordination.x + 5, new_coordination.y, all))
		return ;
	if (hitted_with_wall(new_coordination.x, new_coordination.y + 5, all))
		return ;
	if (hitted_with_wall(new_coordination.x - 5, new_coordination.y, all))
		return ;
	all->player->coor.x = new_coordination.x;
	all->player->coor.y = new_coordination.y;
}

double	get_distance(t_point a, t_point b)
{
	if (b.x == -1 || b.y == -1)
		return (INT_MAX);
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}
