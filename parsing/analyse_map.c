/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:06:35 by amentag           #+#    #+#             */
/*   Updated: 2023/06/20 18:41:31 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_values(t_directions *dir, int i, int j)
{
	dir->top = i - 1;
	dir->down = i + 1;
	dir->right = j + 1;
	dir->left = j - 1;
}

int	surrounded_with_walls(char **map, int i, int j)
{
	t_directions	dir;

	set_values(&dir, i, j);
	if (map[i][j] == '1')
		return (1);
	if (valid_char(map[i][j]) || is_white_space(map[i][j]))
	{
		if (j < ft_strlen(map[dir.top]) && \
			!valid_surrounded(map[i][j], map[dir.top][j]))
			return (0);
		if (j < ft_strlen(map[dir.down]) && \
			!valid_surrounded(map[i][j], map[dir.down][j]))
			return (0);
		if (dir.right == ft_strlen(map[i]) || dir.left == -1)
		{
			if (is_white_space(map[i][j]))
				return (1);
			return (0);
		}
		if (!valid_surrounded(map[i][j], map[i][dir.right])
			|| !valid_surrounded(map[i][j], map[i][dir.left]))
			return (0);
		return (1);
	}
	return (0);
}

void	analyse_map(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if ((i == 0 || i == all->number_lines - 1))
			{
				if (!is_white_space(all->map[i][j]) && all->map[i][j] != '1')
					write_error(2);
			}
			else if (!surrounded_with_walls(all->map, i, j))
			{
				write_error(2);
			}
			j++;
		}
		i++;
	}
}
