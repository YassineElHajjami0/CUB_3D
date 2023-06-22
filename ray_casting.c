/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:30:13 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/22 16:47:40 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	increment(t_point *point, t_point p)
{
	point->x += p.x;
	point->y += p.y;
}

void	set_ray(t_all *all, int i)
{
	t_point	ver;
	t_point	hor;
	double	dist_ver;
	double	dist_hor;

	hor = get_horizontal_touch(all, i);
	ver = get_vertical_touch(all, i);
	dist_ver = get_distance(all->player->coor, ver);
	dist_hor = get_distance(all->player->coor, hor);
	if (dist_ver < dist_hor)
	{
		all->rays[i].coor = ver;
		all->rays[i].hitvertical = true;
		all->rays[i].distance = dist_ver;
	}
	else
	{
		all->rays[i].hitvertical = false;
		all->rays[i].coor = hor;
		all->rays[i].distance = dist_hor;
	}
	all->rays[i].distance = cos((M_PI / 6) - \
		(M_PI / (3 * NUMBER_RAYS)) * i) * all->rays[i].distance;
	all->rays[i].column_height = RATIO / all->rays[i].distance;
}

void	set_ray_facing_direction(t_ray *ray)
{
	ray->facing_up = 0;
	ray->facing_down = 0;
	ray->facing_left = 0;
	ray->facing_right = 0;
	if (ray->ray_angle >= M_PI && ray->ray_angle <= 2 * M_PI)
		ray->facing_up = 1;
	else
		ray->facing_down = 1;
	if ((ray->ray_angle >= 1.5 * M_PI && ray->ray_angle <= 2 * M_PI) \
			|| (ray->ray_angle >= 0 && ray->ray_angle <= 0.5 * M_PI))
		ray->facing_right = 1;
	else
		ray->facing_left = 1;
}

void	set_rays(t_all *all)
{
	int		i;
	double	angle;

	angle = all->player->rotation_angle - (M_PI / 6);
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	i = -1;
	while (++i < NUMBER_RAYS)
	{
		all->rays[i].ray_angle = angle;
		set_ray_facing_direction(all->rays + i);
		set_ray(all, i);
		angle += (M_PI / (3 * NUMBER_RAYS));
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		if (angle < 0)
			angle += 2 * M_PI;
	}
}
