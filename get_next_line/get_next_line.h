/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:07:13 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/21 21:01:13 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>
# include "../cub3d.h"

char	*ft_strjoin(char *sta, char *buff);
char	*get_next_line(int fd);
char	*putinsta(int fd, char *sta);
char	*putleftinsta(char *sta);
char	*putins(char *sta);

#endif
