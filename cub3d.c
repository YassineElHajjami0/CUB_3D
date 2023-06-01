/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:52:44 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/01 11:42:33 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

void init_all(t_all *all)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB_3D");
    all->player = malloc(sizeof(t_player));
    all->player->rotation_speed = 2 * (M_PI / 180);
    all->player->walk_direction = 0;
    all->player->turn_direction = 0;
    all->player->move_speed = 2;

    all->data.img = mlx_new_image(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel, &all->data.line_length, &all->data.endian);
}

int key_hook(int key, t_all *all)
{
    if (key == W)
        all->player->walk_direction = 1;
    else if (key == S)
        all->player->walk_direction = -1;
    else if (key == A)
        all->player->turn_direction = -1;
    else if (key == D)
        all->player->turn_direction = 1;
    else if (key == 53)
        exit(0);
    return (0);
}

int key_released(int keycode, t_all *all)
{
    (void)keycode;
    all->player->turn_direction = 0;
    all->player->walk_direction = 0;
    return 0;
}

int ft_exit()
{
    exit(0);
}

void my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
    if (x < 0 || y < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
        return;
    char *dst;

    dst = all->data.addr + (y * all->data.line_length + x * (all->data.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

bool hitted_with_wall(double x, double y, t_all *all)
{
    int line;
    int col;

    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return 1;

    line = floor(y / 64);
    col = floor(x / 64);

    if (line >= all->number_lines || col >= (int)ft_strlen(all->map[line]))
        return (true);
    if (all->map[line][col] == '1')
        return (true);
    return (false);
}

void update_coordination(t_all *all)
{
    int step;
    t_point new_coordination;
    int line;
    int column;

    if (all->player->rotation_angle > 2 * M_PI)
        all->player->rotation_angle -= 2 * M_PI;
    if (all->player->rotation_angle < 0)
        all->player->rotation_angle += 2 * M_PI;

    if (all->player->rotation_angle >= M_PI && all->player->rotation_angle <= 2 * M_PI)
        all->player->facing_up = 1; // here
    else
        all->player->facing_up = -1;
    if ((all->player->rotation_angle >= 1.5 * M_PI && all->player->rotation_angle <= 2 * M_PI) || (all->player->rotation_angle >= 0 && all->player->rotation_angle <= 0.5 * M_PI))
        all->player->facing_right = 1;
    else
        all->player->facing_right = -1;
    all->player->rotation_angle += all->player->turn_direction * all->player->rotation_speed;

    step = all->player->walk_direction * all->player->move_speed;
    new_coordination.x = all->player->coor.x + cos(all->player->rotation_angle) * step;
    new_coordination.y = all->player->coor.y + sin(all->player->rotation_angle) * step;
    line = (int)(new_coordination.y / 64);
    column = (int)(new_coordination.x / 64);
    if (line >= all->number_lines || column >= (int)ft_strlen(all->map[line]))
        return;
    if (hitted_with_wall(new_coordination.x, new_coordination.y - 5, all))
        return;
    if (hitted_with_wall(new_coordination.x + 5, new_coordination.y, all))
        return;
    if (hitted_with_wall(new_coordination.x, new_coordination.y + 5, all))
        return;
    if (hitted_with_wall(new_coordination.x - 5, new_coordination.y, all))
        return;
    all->player->coor.x = new_coordination.x;
    all->player->coor.y = new_coordination.y;
}

t_point get_vertical_touch(t_all *all, int i)
{
    t_point first;
    double x_step;
    double y_step;
    double p;

    first.x = floor(all->player->coor.x / 64) * 64;
    if (all->rays[i].facing_right)
        first.x += 64;
    first.y = tan(all->rays[i].rayAngle) * (first.x - all->player->coor.x) + all->player->coor.y;
    x_step = 64;
    if (all->rays[i].facing_left)
        x_step *= -1;
    y_step = tan(all->rays[i].rayAngle) * 64;
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
    first.x = (first.y - all->player->coor.y) / tan(all->rays[i].rayAngle) + all->player->coor.x; /// here
    y_step = 64;
    x_step = 64 / tan(all->rays[i].rayAngle);
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

double get_distance(t_point a, t_point b)
{
    if (b.x == -1 || b.y == -1)
        return (INT_MAX);
    return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

void set_ray(t_all *all, int i)
{
    t_point ver;
    t_point hor;

    hor = get_horizontal_touch(all, i);
    ver = get_vertical_touch(all, i);
    if (get_distance(all->player->coor, ver) < get_distance(all->player->coor, hor))
    {
        all->rays[i].coor.x = ver.x;
        all->rays[i].coor.y = ver.y;
    }
    else
    {
        all->rays[i].coor.x = hor.x;
        all->rays[i].coor.y = hor.y;
    }
}

void set_ray_facing_direction(t_ray *ray)
{
    ray->facing_up = 0;
    ray->facing_down = 0;
    ray->facing_left = 0;
    ray->facing_right = 0;
    if (ray->rayAngle >= M_PI && ray->rayAngle <= 2 * M_PI)
        ray->facing_up = 1;
    else
        ray->facing_down = 1;
    if ((ray->rayAngle >= 1.5 * M_PI && ray->rayAngle <= 2 * M_PI) || (ray->rayAngle >= 0 && ray->rayAngle <= 0.5 * M_PI))
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
    // printf("rotation angle = %f\n, turn direction = %d\n, angle = %f\n, FOV = %f\n, num rays = %d",
    //  all->player->rotation_angle, all->player->turn_direction, angle, FOV, NUMBER_RAYS);
    // exit(1);
    // while (++i < NUMBER_RAYS)
    // {
    all->rays[i].rayAngle = angle;
    set_ray_facing_direction(all->rays + 0);
    set_ray(all, 0);
    angle += (FOV / NUMBER_RAYS);
    // }
}

int loop(t_all *all)
{

    mlx_put_image_to_window(all->mlx, all->win, all->data.img, 0, 0);
    // clear_image(all);
    set_rays(all);
    // render3d_projection(all);
    update_coordination(all);
    draw_mini_map(all);
    return (0);
}

void init_player(t_all *all)
{
    int i = 0, j, flag = 0;

    while (i < all->number_lines && !flag)
    {
        j = 0;
        while (j < (int)ft_strlen(all->map[i]))
        {
            if (all->map[i][j] && all->map[i][j] == 'N')
            {
                all->player->coor.x = j * 64;
                all->player->coor.y = i * 64;
                all->player->rotation_angle = 0 * M_PI;
                flag = 1;
                break;
            }
            j++;
        }
        i++;
    }
    if (all->player->rotation_angle >= M_PI && all->player->rotation_angle <= 2 * M_PI)
        all->player->facing_up = 1;
    else
        all->player->facing_up = -1;
    if ((all->player->rotation_angle >= 1.5 * M_PI && all->player->rotation_angle <= 2 * M_PI) || (all->player->rotation_angle >= 0 && all->player->rotation_angle <= 0.5 * M_PI))
        all->player->facing_right = 1;
    else
        all->player->facing_right = -1;
}

int main(int ac, char **av)
{
    t_all *all;

    all = malloc(sizeof(t_all));
    init_all(all);
    parsing(ac, av, all);
    init_player(all);
    mlx_hook(all->win, 2, 0, key_hook, all);
    mlx_hook(all->win, 3, 0, key_released, all);
    mlx_hook(all->win, 17, 0, &ft_exit, NULL);
    mlx_loop_hook(all->mlx, loop, all);
    mlx_loop(all->mlx);
    return 0;
}
