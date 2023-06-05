/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:30:13 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/05 10:56:46 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point get_vertical_touch(t_all *all, int i)
{
    t_point first;
    double  x_step;
    double  y_step;
    double  p;

    first.x = floor(all->player->coor.x / 64) * 64;
    if (all->rays[i].facing_right)
        first.x += 64;
    first.y = tan(all->rays[i].ray_angle) * (first.x - all->player->coor.x) + all->player->coor.y;
    x_step = 64;
    if (all->rays[i].facing_left)
        x_step *= -1;
    y_step = tan(all->rays[i].ray_angle) * 64;
    if (all->rays[i].facing_up && y_step > 0)
        y_step *= -1;
    if (all->rays[i].facing_down && y_step < 0)
        y_step *= -1;
    while (first.x >= 0 && first.x < WINDOW_WIDTH && first.y >= 0 && first.y < WINDOW_HEIGHT)
    {
        p = first.x;
        if (all->rays[i].facing_left)
            p = first.x - 1;
        if (hitted_with_wall(p, first.y, all))
            return (first);
        else
        {
            first.x += x_step;
            first.y += y_step;
        }
    }
    first.x = -1;
    first.y = -1;
    return (first);
}

t_point get_horizontal_touch(t_all *all, int i)
{
    t_point first;
    double x_step;
    double y_step;
    double p;

    first.y = floor(all->player->coor.y / 64) * 64;
    if (all->rays[i].facing_down)
        first.y += 64;
    first.x = (first.y - all->player->coor.y) / tan(all->rays[i].ray_angle) + all->player->coor.x; /// here
    y_step = 64;
    x_step = 64 / tan(all->rays[i].ray_angle);
    // printf("first y = %f\n, first x = %f\n, y_step = %f\n, x_step = %f\n", first.y, first.x, y_step, x_step);
    // exit(1);
    if (all->rays[i].facing_up)
        y_step *= -1;
    if (all->rays[i].facing_right && x_step < 0)
        x_step *= -1;
    if (all->rays[i].facing_left && x_step > 0)
        x_step *= -1;
    while (first.x >= 0 && first.x < WINDOW_WIDTH && first.y >= 0 && first.y < WINDOW_HEIGHT)
    {
        p = first.y;
        if (all->rays[i].facing_up)
            p = first.y - 1;
        // printf("all->player->facing_up = %d, first x = %f\n first y = %f\np = %f\n",all->player->facing_up, first.x, first.y, p);
        // exit(1);
        if (hitted_with_wall(first.x, p, all))
            return (first);
        else
        {
            first.x += x_step;
            first.y += y_step;
        }
    }
    first.x = -1;
    first.y = -1;
    return (first);
}

void set_ray(t_all *all, int i)
{
    t_point ver;
    t_point hor;
    double  dist_ver;
    double  dist_hor;

    hor = get_horizontal_touch(all, i);
    ver = get_vertical_touch(all, i);
    dist_ver = get_distance(all->player->coor, ver);
    dist_hor = get_distance(all->player->coor, hor);
    if (dist_ver < dist_hor)
    {
        all->rays[i].coor.x = ver.x;
        all->rays[i].coor.y = ver.y;
        all->rays[i].hitvertical = true;
        all->rays[i].distance = dist_ver;
    }
    else
    {
        all->rays[i].hitvertical = false;
        all->rays[i].coor.x = hor.x;
        all->rays[i].coor.y = hor.y;
        all->rays[i].distance = dist_hor;
    }
    all->rays[i].distance = cos((FOV / 2) - (FOV / NUMBER_RAYS) * i) * all->rays[i].distance;
    all->rays[i].column_height = 40000 / all->rays[i].distance;
}

void set_ray_facing_direction(t_ray *ray)
{
    ray->facing_up = 0;
    ray->facing_down = 0;
    ray->facing_left = 0;
    ray->facing_right = 0;
    if (ray->ray_angle >= M_PI && ray->ray_angle <= 2 * M_PI)
        ray->facing_up = 1;
    else
        ray->facing_down = 1;
    if ((ray->ray_angle >= 1.5 * M_PI && ray->ray_angle <= 2 * M_PI) || (ray->ray_angle >= 0 && ray->ray_angle <= 0.5 * M_PI))
        ray->facing_right = 1;
    else
        ray->facing_left = 1;
}

void set_rays(t_all *all)
{
    int i;
    double angle;

    angle = all->player->rotation_angle - (FOV / 2);
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
        angle += (FOV / NUMBER_RAYS);
        if (angle > 2 * M_PI)
            angle -= 2 * M_PI;
        if (angle < 0)
            angle += 2 * M_PI;
    }
}