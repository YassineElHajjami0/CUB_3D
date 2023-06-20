/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:17:11 by amentag           #+#    #+#             */
/*   Updated: 2023/06/20 19:50:49 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int key, t_all *all)
{
	if (key == 13)
		all->player->walk_direction = 1;
	else if (key == 1)
		all->player->walk_direction = -1;
	else if (key == 0)
	{
		all->player->flag = 1;
		all->player->walk_direction = -1;
	}
	else if (key == 2)
	{
		all->player->flag = 1;
		all->player->walk_direction = 1;
	}
	else if (key == 124)
		all->player->turn_direction = 1;
	else if (key == 123)
		all->player->turn_direction = -1;
	else if (key == 53)
		exit(0);
	return (0);
}

int	key_released(int keycode, t_all *all)
{
	(void)keycode;
	all->player->turn_direction = 0;
	all->player->walk_direction = 0;
	all->player->flag = 0;
	return (0);
}
