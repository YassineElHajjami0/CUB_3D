#include "../cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
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


int    ft_atoi(const char *str)
{
    long int    res;
    long int    tmp;
    int            sign;

    res = 0;
    sign = 1;
    while (*str == ' '  || (*str >= 9 && *str <= 13))
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

char	*ft_strchr(const char *str, int c)
{
	size_t	len;
	size_t	i;

	//segfault 
	if (!str)
		return (NULL);
	////

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != 0 && s2[i] != 0) && i < n - 1)
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
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