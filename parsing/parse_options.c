#include "../cub3d.h"

//check if a line contain only spaces
bool valid_line(char *line)
{
    int     i = 0;
    while (line[i] && is_white_space(line[i]))
        i++;
    if (!line[i])
        return (false);
    return (true);
}

int valide_option(char *str)
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

bool    file_end_with_xpm(t_info *info)
{
    int i;

    i = ft_strlen(info->north) - 1;
    if (i - 3 <= 0 || info->north[i] != 'm' || info->north[i - 1] != 'p' || info->north[i - 2] != 'x' || info->north[i - 3] != '.')
        return (false);
    i = ft_strlen(info->south) - 1;
    if (i - 3 <= 0 || info->south[i] != 'm' || info->south[i - 1] != 'p' || info->south[i - 2] != 'x' || info->south[i - 3] != '.')
        return (false);
    i = ft_strlen(info->west) - 1;
    if (i - 3 <= 0 || info->west[i] != 'm' || info->west[i - 1] != 'p' || info->west[i - 2] != 'x' || info->west[i - 3] != '.')
        return (false);
    i = ft_strlen(info->east) - 1;
    if (i - 3 <= 0 || info->east[i] != 'm' || info->east[i - 1] != 'p' || info->east[i - 2] != 'x' || info->east[i - 3] != '.')
        return (false);
    return (true);
}

bool    files_exist(t_info *info)
{
    int fd;

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


bool    check_range(t_info *info, int type)
{
    int *n;
    int i;

    if (type == 5)
        n = info->floor;
    else 
        n = info->ceil;
    i = 0;    
    while (n[i])
    {
        if (n[i] < 0 || n[i] > 255)
            return (false);
        i++;
    }
    return (true);
}

bool    init_rgb(t_info *info, int type, char *line)
{
    char *rgb_value;
    int i = 0;
    int flag;
    int number;

    number = 0;
    rgb_value = ft_strtrim(line, " \t\r\n");
    while (rgb_value[i])
    {
        while (rgb_value[i] && is_white_space(rgb_value[i]))
            i++;
        flag = 0;
        while (rgb_value[i] && ft_isdigit(rgb_value[i]))
        {
            flag = 1;
            i++;
        }
        if (!flag)
            return (false);
        number++;
        while (rgb_value[i] && is_white_space(rgb_value[i]))
            i++;
        
        if (number < 3)
        {
            if (rgb_value[i] != ',')
                return (false);
            i++;
        }
    
    }
    if (number != 3)
        return (false);
    i = 0;
    number = 0;
    while (number < 3)
    {
        if (type == 5)
        {
            if (info->floor[number] != -1)
                return (false);
            info->floor[number] = ft_atoi(rgb_value+ i);
        }
        else
        {
            if (info->ceil[number] != -1)
                return (false);
            info->ceil[number] = ft_atoi(rgb_value+ i);
        }
        while (rgb_value[i] && (ft_isdigit(rgb_value[i]) || is_white_space(rgb_value[i])))
            i++;
        if (rgb_value[i] == ',')
            i++;
        number++;
    }
    if (!check_range(info, type))
        return (false);
    return (true);
}

//what is "\r"
bool    init_info(t_info *info, int type, char *line)
{
    if (type == 1 && !info->north) // "NO "
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

bool    parse_option(int fd, t_info *info)
{
    char *line;
    int i = 0; //-> 6
    int j;
    int type;

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
            if (i == 5)
                type = 0;
        }
    }
    if (!files_exist(info))
        return (false);
    return (true);
}

