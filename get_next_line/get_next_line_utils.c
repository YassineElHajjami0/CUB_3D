/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:30:01 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/05/29 13:28:18 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin(char *sta, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!sta)
	{
		sta = (char *)malloc(1);
		sta[0] = '\0';
	}
	if (!sta || !buff)
		return (NULL);
	s = malloc((ft_strlen(sta) + ft_strlen(buff)) + 1);
	if (!s)
		write_error(2);
	i = -1;
	j = 0;
	while (sta[++i] != '\0')
		s[i] = sta[i];
	while (buff[j] != '\0')
		s[i++] = buff[j++];
	s[ft_strlen(sta) + ft_strlen(buff)] = '\0';
	free(sta);
	sta = NULL;
	return (s);
}

char	*putleftinsta(char *sta)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (sta[i] && sta[i] != '\n')
		i++;
	if (!sta[i])
	{
		free(sta);
		return (NULL);
	}
	s = (char *)malloc(ft_strlen(sta) - i + 1);
	if (!s)
		write_error(2);
	i++;
	j = 0;
	while (sta[i])
		s[j++] = sta[i++];
	s[j] = '\0';
	free(sta);
	sta = NULL;
	return (s);
}

// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*p;

// 	i = 0;
// 	while (s1[i])
// 		i++;
// 	p = (char *)malloc(sizeof(char) * i + 1);
// 	if (!p)
// 		write_error(2);
// 	i = -1;
// 	while (s1[++i])
// 		p[i] = s1[i];
// 	p[i] = '\0';
// 	return (p);
// }
