/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:11:37 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/17 11:47:31 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"

void write_error(int n)
{
    write(n, "ERROR\n", 6);
    exit(1);
}

// char **get_linee(char *choosedmap)
char **get_linee(int fd)
{
    // int fd;
    char *line;
    char *str;

    line = NULL;
    str = ft_strdup("");
    // fd = open(choosedmap, O_RDWR);
    // if (fd == -1)
    // {
    //     write(2, "Eroor\n", 6);
    //     exit(1);
    // }
    line = get_next_line(fd);
    while (!valid_line(line))
        line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '\n')
        {
            write(2, "Eroor\n", 6);
            exit(1);
        }
        str = ft_strjoin(str, line);
        free(line);
        line = get_next_line(fd);
    }
    return (free(line), ft_split(str, '\n'));
}

void tba3_map(t_all *all)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (all->map[i])
    {
        j = 0;
        while (all->map[i][j])
        {
            printf("%c", all->map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}


bool valid_char(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool valid_surrounded(char c1, char c2)
{
    if (c2 == '1')
        return (true);
    if (is_white_space(c1) && is_white_space(c2))
        return (true);
    if (valid_char(c1) && valid_char(c2))
        return (true);
    return (false);
}

int surrounded_with_walls(char** map, int i , int j)
{
    char c = map[i][j];
    int top = i - 1;
    int down = i + 1;
    int right = j + 1;
    int left = j - 1;

    if (c == '1')
        return (1);
    if (valid_char(c) || is_white_space(c))
    {
        if (!valid_surrounded(c, map[top][j]) || !valid_surrounded(c, map[down][j]))
            return (0);
        if (right == ft_strlen(map[i]) || left == -1)
            return (0);
        if (!valid_surrounded(c, map[i][right]) || !valid_surrounded(c, map[i][left]))
            return (0);
        return (1);
    }
    return (0);
}

void analyse_map(t_all *all)
{
    int i;
    int j;

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
            else if (!surrounded_with_walls(all->map, i , j))
                write_error(2);
            j++;
        }
        i++;
    }
}

void    parsing(int fd, t_all *all)
{
    int i;
    int found;

    found = 0;
    i = 0;
    all->number_lines = 0;
    i--;    
    all->map = get_linee(fd);
    while (all->map[all->number_lines])
        all->number_lines++;
    analyse_map(all);
}
