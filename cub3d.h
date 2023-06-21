/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amentag <amentag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:37:35 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/21 21:01:24 by amentag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "./get_next_line/get_next_line.h" 
# define WINDOW_WIDTH 1980
# define WINDOW_HEIGHT 1024
# define NUMBER_RAYS WINDOW_WIDTH
# define TILE_SIZE 64

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	int		map_width;
	int		map_height;
	char	**tab;
}	t_map;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	t_point	coor;
	int		side;
	int		turn_direction;
	int		walk_direction;
	double	rotation_angle;
	int		move_speed;
	double	rotation_speed;
	int		facing_up;
	int		facing_right;
	int		flag;
}	t_player;

typedef struct s_ray
{
	double	distance;
	double	ray_angle;
	bool	hitvertical;
	int		facing_up;
	int		facing_down;
	int		facing_left;
	int		facing_right;
	t_point	coor;
	double	column_height;
}	t_ray;

typedef struct s_directions
{
	int		top;
	int		down;
	int		right;
	int		left;
}	t_directions;

typedef struct s_all
{
	char			**map;
	char			*choosed_map;
	int				number_lines;
	int				i;
	int				j;
	int				k;
	int				z;
	t_data			data;
	t_data			north;
	t_data			south;
	t_data			west;
	t_data			east;
	void			*mlx;
	void			*win;
	t_player		*player;
	t_ray			rays[NUMBER_RAYS];
	void			*wall;
	unsigned int	*north_array;
	unsigned int	*south_array;
	unsigned int	*west_array;
	unsigned int	*east_array;
}	t_all;

typedef struct s_info
{
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	int		ceil[3];
	int		floor[3];
	int		map_start_at_line;
	int		width;
	int		height;
}	t_info;

char			**ft_split(char const *s, char c);
char			*get_next_line(int fd);
void			write_error(int n);
void			parsing(int fd, t_all *all);
void			draw_mini_map(t_all *all);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
void			init_all(t_all *all, t_info *info);
void			init_player(t_all *all);
void			set_ray(t_all *all, int i);
void			set_ray_facing_direction(t_ray *ray);
void			set_rays(t_all *all);
bool			hitted_with_wall(double x, double y, t_all *all);
double			get_distance(t_point a, t_point b);
void			update_coordination(t_all *all);
int				is_white_space(char c);
bool			invalid_line(char *line);
int				valide_option(char *str);
bool			files_exist(t_info *info);
bool			init_info(t_info *info, int type, char *line);
bool			parse_option(int fd, t_info *info);
bool			valid_line(char *line);
int				valide_option(char *str);
bool			file_end_with_xpm(t_info *info);
bool			files_exist(t_info *info);
bool			check_range(t_info *info, int type);
bool			valid_char(char c);
bool			valid_surrounded(char c1, char c2);
int				surrounded_with_walls(char **map, int i, int j);
void			analyse_map(t_all *all);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *str, int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
unsigned int	*get_direction(t_all *all, int column);
void			draw_column(t_all *all, int column, int start, int end);
void			rendering_walls(t_all *all);
void			draw_floor(t_all *all);
void			draw_ceil(t_all *all);
int				key_hook(int key, t_all *all);
int				key_released(int keycode, t_all *all);
t_point			get_vertical_touch(t_all *all, int i);
t_point			get_horizontal_touch(t_all *all, int i);
void			increment(t_point *point, t_point p);
t_point			get_vertical_touch(t_all *all, int i);
t_point			get_horizontal_touch(t_all *all, int i);
#endif