/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_fns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:47:07 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/01 15:24:49 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

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

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (1);
	line = floor(y / 64);
	col = floor(x / 64);
	if (line >= all->number_lines || col >= (int)ft_strlen(all->map[line]))
		return (true);
	if (all->map[line][col] == '1')
		return (true);
	return (false);
}

void	player_rotation_and_facing(t_all *all, int *step,
	t_point *new_coordination)
{
	if (all->player->rotation_angle > 2 * M_PI)
		all->player->rotation_angle -= 2 * M_PI;
	if (all->player->rotation_angle < 0)
		all->player->rotation_angle += 2 * M_PI;
	if (all->player->rotation_angle >= M_PI
		&& all->player->rotation_angle <= 2 * M_PI)
		all->player->facing_up = 1;
	else
		all->player->facing_up = -1;
	if ((all->player->rotation_angle >= 1.5 * M_PI
			&& all->player->rotation_angle <= 2 * M_PI)
		|| (all->player->rotation_angle >= 0
			&& all->player->rotation_angle <= 0.5 * M_PI))
		all->player->facing_right = 1;
	else
		all->player->facing_right = -1;
	all->player->rotation_angle += all->player->turn_direction * \
		all->player->rotation_speed;
	*step = all->player->walk_direction * all->player->move_speed;
	new_coordination->x = all->player->coor.x + \
		cos(all->player->rotation_angle) * (*step);
	new_coordination->y = all->player->coor.y + \
		sin(all->player->rotation_angle) * (*step);
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
