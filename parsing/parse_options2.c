/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:16:23 by amentag           #+#    #+#             */
/*   Updated: 2023/06/22 16:05:44 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_white_space(line[i]))
		i++;
	if (!line[i])
		return (false);
	return (true);
}

int	valide_option(char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (1);
	if (!ft_strncmp(str, "SO ", 3))
		return (2);
	if (!ft_strncmp(str, "WE ", 3))
		return (3);
	if (!ft_strncmp(str, "EA ", 3))
		return (4);
	if (!ft_strncmp(str, "F ", 2))
		return (5);
	if (!ft_strncmp(str, "C ", 2))
		return (6);
	return (0);
}

bool	file_end_with_xpm(t_info *info)
{
	int	i;

	i = ft_strlen(info->north) - 1;
	if (i - 3 <= 0 || info->north[i] != 'm' || \
		info->north[i - 1] != 'p' || \
		info->north[i - 2] != 'x' || info->north[i - 3] != '.')
		return (false);
	i = ft_strlen(info->south) - 1;
	if (i - 3 <= 0 || info->south[i] != 'm' || \
		info->south[i - 1] != 'p' || \
		info->south[i - 2] != 'x' || info->south[i - 3] != '.')
		return (false);
	i = ft_strlen(info->west) - 1;
	if (i - 3 <= 0 || info->west[i] != 'm' || \
		info->west[i - 1] != 'p' || \
		info->west[i - 2] != 'x' || info->west[i - 3] != '.')
		return (false);
	i = ft_strlen(info->east) - 1;
	if (i - 3 <= 0 || info->east[i] != 'm' \
		|| info->east[i - 1] != 'p' || \
		info->east[i - 2] != 'x' || info->east[i - 3] != '.')
		return (false);
	return (true);
}

bool	files_exist(t_info *info)
{
	int	fd;

	fd = open(info->north, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	fd = open(info->south, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	fd = open(info->east, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	fd = open(info->west, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	if (!file_end_with_xpm(info))
		return (false);
	return (true);
}

bool	check_range(t_info *info, int type)
{
	int	*n;
	int	i;

	if (type == 5)
		n = info->floor;
	else
		n = info->ceil;
	i = 0;
	while (i < 3)
	{
		if (n[i] < 0 || n[i] > 255)
			return (false);
		i++;
	}
	return (true);
}
