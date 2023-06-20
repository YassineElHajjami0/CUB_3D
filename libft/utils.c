/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:02:40 by amentag           #+#    #+#             */
/*   Updated: 2023/06/20 19:03:21 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_atoi(const char *str)
{
	long int	res;
	long int	tmp;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
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
