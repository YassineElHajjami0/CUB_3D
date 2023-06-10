/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paarsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:11:37 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/31 16:02:17 by yel-hajj         ###   ########.fr       */
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

void check_element(char **map, int i, int j)
{
    if (map[i][j + 1] == '\0' || (map[i][j + 1] != '0' && map[i][j + 1] != '1' && map[i][j + 1] != 'N' && map[i][j + 1] != 'S' && map[i][j + 1] != 'E' && map[i][j + 1] != 'W'))
        write_error(2);
    else if (j - 1 < 0 || (map[i][j - 1] != '0' && map[i][j - 1] != '1' && map[i][j - 1] != 'N' && map[i][j - 1] != 'S' && map[i][j - 1] != 'E' && map[i][j - 1] != 'W'))
        write_error(2);
    else if (!map[i + 1] || (map[i + 1][j] != '0' && map[i + 1][j] != '1' && map[i + 1][j] != 'N' && map[i + 1][j] != 'S' && map[i + 1][j] != 'E' && map[i + 1][j] != 'W'))
        write_error(2);
    else if (i - 1 < 0 || (map[i - 1][j] != '0' && map[i - 1][j] != '1' && map[i - 1][j] != 'N' && map[i - 1][j] != 'S' && map[i - 1][j] != 'E' && map[i - 1][j] != 'W'))
        write_error(2);
}

void is_sourounded_with_walls(t_all *all)
{
    all->i = 0;
    all->j = 0;

    while (all->map[all->i])
    {
        all->j = 0;
        while (all->map[all->i][all->j])
        {
            if (all->map[all->i][all->j] != '1' && all->map[all->i][all->j] != '0' && all->map[all->i][all->j] != ' ' && all->map[all->i][all->j] != 'N' && all->map[all->i][all->j] != 'S' && all->map[all->i][all->j] != 'E' && all->map[all->i][all->j] != 'W')
                write_error(2);
            if (all->map[all->i][all->j] == '0')
                check_element(all->map, all->i, all->j);
            if (all->map[all->i][all->j] == 'S')
                check_element(all->map, all->i, all->j);
            if (all->map[all->i][all->j] == 'W')
                check_element(all->map, all->i, all->j);
            if (all->map[all->i][all->j] == 'E')
                check_element(all->map, all->i, all->j);
            if (all->map[all->i][all->j] == 'N')
                check_element(all->map, all->i, all->j);

            all->j++;
        }
        all->i++;
    }
}

void analyse_map(t_all *all)
{
    is_sourounded_with_walls(all);
}

void 
// parsing(int ac, char **av, t_all *all)
parsing(int fd, t_all *all)
{
    int i;

    i = 0;
    all->number_lines = 0;
    // if (ac != 2)
    //     write_error(2);
    // while (av[1][i])
    //     i++;
    i--;
    
    // all->choosed_map = av[1];
    // all->map = get_linee(all->choosed_map);
    all->map = get_linee(fd);
    while (all->map[all->number_lines])
        all->number_lines++;
    // analyse_map(all);
    // tba3_map(all);
}
