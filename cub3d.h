/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:37:35 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/06/04 11:51:35 by yel-hajj         ###   ########.fr       */
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
# define WINDOW_WIDTH 1980
# define WINDOW_HEIGHT 1024
# define SCALE 0.5
# define THICK 1
# define NUMBER_RAYS (WINDOW_WIDTH / THICK)
# define TILE_SIZE 64
# define A 0
# define S 1
# define W 13
# define D 2
# define LEFT 123
# define RIGHT 124
# define FOV (M_PI / 3)

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

typedef struct	 s_info
{
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	char	*ceil;
	char	*floor;
	int		map_start_at_line;
	int		width;
	int		height;
}	t_info;

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
void	write_error(int n);
void	parsing(int ac, char **av, t_all *all);
void	draw_mini_map(t_all *all);
void	my_mlx_pixel_put(t_all *all, int x, int y, int color);
void	init_all(t_all *all);
void	init_player(t_all *all);
void	set_ray(t_all *all, int i);
void	set_ray_facing_direction(t_ray *ray);
void	set_rays(t_all *all);
bool	hitted_with_wall(double x, double y, t_all *all);
double	get_distance(t_point a, t_point b);
void	update_coordination(t_all *all);

#endif