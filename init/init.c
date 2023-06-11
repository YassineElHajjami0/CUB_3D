/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:22:38 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/01 13:43:28 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_all(t_all *all)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB_3D");
    all->player = malloc(sizeof(t_player));
    all->player->rotation_speed = 2 * (M_PI / 180);
    all->player->walk_direction = 0;
    all->player->turn_direction = 0;
    all->player->move_speed = 10;

    all->data.img = mlx_new_image(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel,
        &all->data.line_length, &all->data.endian);

    all->north.img = mlx_xpm_file_to_image(all->mlx, "./textures/north.xpm", &(all->z), &(all->k));
    all->north.addr = mlx_get_data_addr(all->north.img, &all->north.bits_per_pixel, &all->north.line_length, &all->north.endian);
    all->north_array = (unsigned int *)all->north.addr;
}

void    init_player_facing_direction(t_all *all)
{
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
}

double get_rotation_angle(char c)
{
    if (c == 'N')
        return (1.5 * M_PI);
    if (c == 'S')
        return (0.5 * M_PI);
    if (c == 'W')
        return (M_PI);
    return (0);
}

void init_player(t_all *all)
{
    int i;
    int j;
    static int flag;

    i = -1;
    while (++i < all->number_lines)
    {
        j = -1;
        while (++j < (int)ft_strlen(all->map[i]))
        {
            if (all->map[i][j] && (all->map[i][j] == 'N' || all->map[i][j] == 'S' || all->map[i][j] == 'E' || all->map[i][j] == 'W'))
            {
                if (flag)
                    write_error(2);
                all->player->coor.x = j * 64;
                all->player->coor.y = i * 64;
                all->player->rotation_angle = get_rotation_angle(all->map[i][j]);
                flag = 1;
            }
        }
    }
    init_player_facing_direction(all);
}


