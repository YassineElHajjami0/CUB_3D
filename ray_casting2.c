/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:05:12 by amentag           #+#    #+#             */
/*   Updated: 2023/06/21 20:28:03 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_first_x(t_all *all, int i, t_point first)
{
	return ((first.y - all->player->coor.y) / \
		tan(all->rays[i].ray_angle) + all->player->coor.x);
}

double	get_first_y(t_all *all, int i, t_point first)
{
	return (tan(all->rays[i].ray_angle) * \
		(first.x - all->player->coor.x) + all->player->coor.y);
}

t_point	get_vertical_touch(t_all *all, int i)
{
	t_point	first;
	t_point	steps;
	double	p;

	first.x = floor(all->player->coor.x / 64) * 64;
	if (all->rays[i].facing_right)
		first.x += 64;
	first.y = get_first_y(all, i, first);
	steps.x = 64;
	if (all->rays[i].facing_left)
		steps.x *= -1;
	steps.y = tan(all->rays[i].ray_angle) * 64;
	if ((all->rays[i].facing_up && steps.y > 0) || \
		(all->rays[i].facing_down && steps.y < 0))
		steps.y *= -1;
	while (1)
	{
		p = first.x;
		if (all->rays[i].facing_left)
			p = first.x - 1;
		if (hitted_with_wall(p, first.y, all))
			return (first);
		increment(&first, steps);
	}
	return (first);
}

t_point	get_horizontal_touch(t_all *all, int i)
{
	t_point	first;
	t_point	steps;
	double	p;

	first.y = floor(all->player->coor.y / 64) * 64;
	if (all->rays[i].facing_down)
		first.y += 64;
	first.x = get_first_x(all, i, first);
	steps.y = 64;
	steps.x = 64 / tan(all->rays[i].ray_angle);
	if (all->rays[i].facing_up)
		steps.y *= -1;
	if ((all->rays[i].facing_right && steps.x < 0) || \
		(all->rays[i].facing_left && steps.x > 0))
		steps.x *= -1;
	while (1)
	{
		p = first.y;
		if (all->rays[i].facing_up)
			p = first.y - 1;
		if (hitted_with_wall(first.x, p, all))
			return (first);
		increment(&first, steps);
	}
	return (first);
}
