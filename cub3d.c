/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:52:44 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/01 14:02:48 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

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

int loop(t_all *all)
{

    mlx_put_image_to_window(all->mlx, all->win, all->data.img, 0, 0);
    // clear_image(all);
    update_coordination(all);
    set_rays(all);
    // render3d_projection(all);
    draw_mini_map(all);
    return (0);
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
