/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:22:38 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/16 12:10:59 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_all(t_all *all, t_info *info)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB_3D");
    all->player = malloc(sizeof(t_player));
    all->player->rotation_speed = 4 * (M_PI / 180);
    all->player->walk_direction = 0;
    all->player->turn_direction = 0;
    all->player->flag = 0;
    all->player->move_speed = 5;


    all->data.img = mlx_new_image(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel,
        &all->data.line_length, &all->data.endian);

    all->north.img = mlx_xpm_file_to_image(all->mlx, info->north, &(all->z), &(all->k));
    all->north.addr = mlx_get_data_addr(all->north.img, &all->north.bits_per_pixel, &all->north.line_length, &all->north.endian);
    all->north_array = (unsigned int *)all->north.addr;

    all->east.img = mlx_xpm_file_to_image(all->mlx, info->east, &(all->z), &(all->k));
    all->east.addr = mlx_get_data_addr(all->east.img, &all->east.bits_per_pixel, &all->east.line_length, &all->east.endian);
    all->east_array = (unsigned int *)all->east.addr;

    all->west.img = mlx_xpm_file_to_image(all->mlx, info->west, &(all->z), &(all->k));
    all->west.addr = mlx_get_data_addr(all->west.img, &all->west.bits_per_pixel, &all->west.line_length, &all->west.endian);
    all->west_array = (unsigned int *)all->west.addr;

    all->south.img = mlx_xpm_file_to_image(all->mlx, info->south, &(all->z), &(all->k));
    all->south.addr = mlx_get_data_addr(all->south.img, &all->south.bits_per_pixel, &all->south.line_length, &all->south.endian);
    all->south_array = (unsigned int *)all->south.addr;
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
                all->player->coor.x = j * 64 + 32;
                all->player->coor.y = i * 64 + 32;
                all->player->rotation_angle = get_rotation_angle(all->map[i][j]);
                flag = 1;
            }
        }
    }
}


