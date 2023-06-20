/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:11:37 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/20 18:33:54 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"

void	write_error(int n)
{
	write(n, "ERROR\n", 6);
	exit(1);
}

char	**get_linee(int fd)
{
	char	*line;
	char	*str;

	line = NULL;
	str = ft_strdup("");
	line = get_next_line(fd);
	while (!valid_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (line[0] == '\n')
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		str = ft_strjoin(str, line);
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), ft_split(str, '\n'));
}

bool	valid_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool	valid_surrounded(char c1, char c2)
{
	if (c2 == '1')
		return (true);
	if (is_white_space(c1) && is_white_space(c2))
		return (true);
	if (valid_char(c1) && valid_char(c2))
		return (true);
	return (false);
}

void	parsing(int fd, t_all *all)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	all->number_lines = 0;
	i--;
	all->map = get_linee(fd);
	while (all->map[all->number_lines])
		all->number_lines++;
	analyse_map(all);
}
