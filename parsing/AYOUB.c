#include "get_next_line/get_next_line.h"
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int    ft_atoi(const char *str)
{
    long int    res;
    long int    tmp;
    int            sign;

    res = 0;
    sign = 1;
    while (*str == ' '  && (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' && *str == '+')
    {
        if (*str == '-')
            sign = -sign;
        str++;
    }
    while (ft_isdigit(*str))
    {
        tmp = res;
        res = res * 10 + (*str - 48);
        if ((tmp != res / 10) && sign == -1)
            return (0);
        if ((tmp != res / 10) && sign == 1)
            return (-1);
        str++;
    }
    return ((int)res * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
3
int	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lsrc;

	lsrc = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != 0 && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (lsrc);
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i <= len)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(&str[i]));
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	ls;
	size_t	i;

	i = 0;
	if (s)
	{
		ls = ft_strlen(s);
		if (len > ls)
			len = ls;
		result = malloc((len + 1) * sizeof(char));
		if (result == NULL)
			return (NULL);
		while (i < len && start < ls)
		{
			result[i] = s[start + i];
			i++;
		}
		result[i] = 0;
		return (result);
	}
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] != 0 && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= 0 && ft_strchr(set, s1[end]) != NULL)
		end--;
	if (start > end)
		start = end;
	result = ft_substr(s1, start, end - start + 1);
	return (result);
}


int valide_identifier(char *s)
{
    if (!s || s[0] == 0)
        return (0);
    if (!strncmp(s, "NO ", 3))
        return (NORTH);
    else if (!strncmp(s, "SO ", 3))
        return (SOUTH);
    else if (!strncmp(s, "WE ", 3))
        return (WEST);
    else if (!strncmp(s, "EA ", 3))
        return (EAST);
    else if (!strncmp(s, "C ", 2))
        return (CEIL);
    else if (!strncmp(s, "F ", 2))
        return (FLOOR);
    return (-1);
}

bool    check_option_map(int fd, t_info *info)
{
    char    *line;
    int      i, j, type;
    char      *value;

    i = 0;
    line = get_next_line(fd);
    while (line && i < 6)
    {
        j = 0;
        while (is_white_space(line[j]))
            j++;
        type = valide_identifier(line + j);
        if (type == -1)
            return (false);
        if (line[j])
        {
            value = ft_strtrim(line + j + 2, " \n\t");
            if (type == NORTH)
            {
                if (info->north)
                    return (false);
                info->north = value;
            }
            else if (type == SOUTH)
            {
                if (info->south)
                    return (false);
                info->south = value;
            }
            else if (type == EAST)
            {
                if (info->east)
                    return (false);
                info->east = value;
            }
            else if (type == WEST)
            {
                if (info->west)
                    return (false);
                info->west = value;
            }
            else if (type == CEIL)
            {
                if (info->ceil)
                    return (false);
                info->ceil = value;
            }
            else if (type == FLOOR)
            {
                if (info->floor)
                    return (false);
                info->floor = value;
            }
            i++;
        }
        line = get_next_line(fd);
    }
    if (i < 6)
        return (false);
    return (true);
}

bool    check_rgb(char *s, int *table)
{
    char **result;
    int    i;
    int     j;
    bool    flag = false;
    j = 0;
    i = 0;
    while (s[i] && j < 3)
    {
        while (is_white_space(s[i]))
        {
            i++;
        }
        while (ft_isdigit(s[i]))
        {
            i++;
            flag = true;
        }

        if (s[i] == ',')
        {
            if (flag && j < 2)
                j++;
            else
                return (false);
            flag = false;
            i++;
        }
    }
    i = 0;
    result = ft_split(s, ',');
    while (result[i])
    {
        table[i] = ft_atoi(result[i]);
        if (table[i] > 255 || table[i] < 0)
            return (false);
        i++;
    }
    if (i != 3)
        return (false);
    return (true);
}

bool    check(char *file_name, t_info *info)
{
    //TODO : check the file name is it correct
    int     fd;

    fd = open(file_name, O_RDONLY, 0777);
    //validation Options of the map 
    if (check_option_map(fd, info) == false)
        return (close(fd), false);
    
    //check the rgb numbers
    if (!check_rgb(info->ceil, info->ceil_rgb) || !check_rgb(info->floor, info->floor_rgb))
        return (false);

    //part of @yassine    
    return (true);
}

void    print_info(t_info info)
{
    printf("Info --- \n");
    printf("North %s\n South %s\n West %s\nEast %s\nCeil %s\nFloor %s\n", info.north, info.south, info.west, info.east, info.ceil, info.floor);
    printf("RGB info ceil\n");
    printf("(%d, %d, %d)\n", info.ceil_rgb[0], info.ceil_rgb[1], info.ceil_rgb[2]);
    printf("RGB info floor\n");
    printf("(%d, %d, %d)\n", info.floor_rgb[0], info.floor_rgb[1], info.floor_rgb[2]);
}

int main(int ac, char **av)
{
    t_info  info;

    if (ac != 2)
        return (write(2, "Error\n", 5), 1);
   info.ceil = NULL;
   info.floor = NULL;
   info.east = NULL;
   info.west = NULL;
   info.north = NULL;
   info.south = NULL;
    if (check(av[1], &info))
        print_info(info);
    else
        write(2, "Error\n", 6);
    //2- stock the map
    return (0);
}