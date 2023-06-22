/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:53:55 by amentag           #+#    #+#             */
/*   Updated: 2023/06/22 16:04:16 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	valid_rgb2(char *rgb_value, int *number, int *flag, int *i)
{
	while (rgb_value[*i] && *number < 3)
	{
		while (is_white_space(rgb_value[*i]))
			(*i)++;
		if (ft_isdigit(rgb_value[*i]))
			break ;
		if (rgb_value[*i] != ',')
			return (false);
		else
		{
			if (*flag == 0)
				return (false);
			*flag = 0;
			(*i)++;
		}
	}
	return (true);
}

bool	valid_rgb(char *rgb_value)
{
	int	i;
	int	flag;
	int	number;

	i = 0;
	number = 0;
	while (rgb_value[i])
	{
		flag = 0;
		while (rgb_value[i] && ft_isdigit(rgb_value[i]))
		{
			flag = 1;
			i++;
		}
		if (!flag)
			return (false);
		number++;
		if (!valid_rgb2(rgb_value, &number, &flag, &i))
			return (false);
	}
	return (number == 3);
}

bool	init_rgb(t_info *info, int type, char *line)
{
	char	*rgb;
	int		i;
	int		flag;
	int		number;
	int		*n;

	rgb = ft_strtrim(line, " \t\r\n");
	if (!valid_rgb(rgb))
		return (free(rgb), false);
	i = 0;
	number = -1;
	n = info->ceil;
	if (type == 5)
		n = info->floor;
	while (++number < 3)
	{
		if (n[number] != -1)
			return (false);
		n[number] = ft_atoi(rgb + i);
		while (rgb[i] && (ft_isdigit(rgb[i]) || is_white_space(rgb[i])))
			i++;
		if (rgb[i] == ',')
			i++;
	}
	return (free(rgb), check_range(info, type));
}

bool	init_info(t_info *info, int type, char *line)
{
	if (type == 1 && !info->north)
		info->north = ft_strtrim(line + 3, " \t\r\n");
	else if (type == 2 && !info->south)
		info->south = ft_strtrim(line + 3, " \t\r\n");
	else if (type == 3 && !info->west)
		info->west = ft_strtrim(line + 3, " \t\r\n");
	else if (type == 4 && !info->east)
		info->east = ft_strtrim(line + 3, " \t\r\n");
	else
	{
		if (!init_rgb(info, type, line + 2))
			return (false);
	}
	return (true);
}

bool	parse_option(int fd, t_info *info)
{
	char	*line;
	int		i;
	int		j;
	int		type;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (valid_line(line))
		{
			j = 0;
			while (line[j] && is_white_space(line[j]))
				j++;
			type = valide_option(line + j);
			if (!type)
				return (false);
			if (!init_info(info, type, line + j))
				return (false);
			i++;
		}
		free(line);
	}
	return (files_exist(info));
}
