#include "../cub3d.h"

void	draw_line(t_all *all, double x, double y, double endx, double endy)
{
	double delta_y;
	double delta_x;
	int		steps;
	double	x_step;
	double	y_step;

	delta_y = endy - y;
	delta_x = endx - x;

	if (fabs(delta_x) > fabs(delta_y))
		steps = fabs(delta_x);
	else
		steps = fabs(delta_y);
	x_step = delta_x / steps;
	y_step = delta_y / steps;
	while (steps--)
	{
		my_mlx_pixel_put(all, x, y, 0x871F78);
		x += x_step;
		y += y_step;
	}
}

void	draw_player(t_all *all)
{
	int	i;
	int	j;

	i = -5;

	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{			
			my_mlx_pixel_put(all, (all->player->coor.x + j) * SCALE , (all->player->coor.y+ i) * SCALE, 0x6264B7);
			j++;
		}
		i++;
	}
	// exit(0);
}

void	draw_squar(t_all *all, double posx , double posy, char character)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (character == '1')
				my_mlx_pixel_put(all, (posx + j) * SCALE, (posy + i) * SCALE, 0x4E1852);
			else if (character != ' ')
				my_mlx_pixel_put(all, (posx + j) * SCALE, (posy + i) * SCALE, 0xdfbdff);
			j++;
		}
		i++;
	}
}

// void    draw_mini_map(t_all *all)
// {
//     int i = 0;
//     int j = 0;
//     // static int flag = 1;
//     while (i < 7)
// 	{
// 		j = 0;
// 		while (j < (int)ft_strlen(all->map[i]))
// 		{
// 			draw_squar(all, j * 64, i * 64, all->map[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
//     draw_player(all);
// 	int z = -1;
// 	while (++z < NUMBER_RAYS)
// 		draw_line(all, all->player->coor.x, all->player->coor.y, all->rays[z].coor.x, all->rays[z].coor.y);
// }


unsigned int	get_color(t_all *all, int x, int y)
{
	double	posx; 
	double	posy;

	posx = all->player->coor.x - 3 * TILE_SIZE / 2 + x;
	posy = all->player->coor.y - 3 * TILE_SIZE / 2 + y;


	if (posy / 64 <  0 || posy / 64 >= all->number_lines)
		return (0x4E1852);

	if (posx / 64 <  0 || posx / 64 >= ft_strlen(all->map[(int)(posy / 64)]))
		return (0x4E1852);


	if (all->map[(int)(posy / 64)][(int)(posx / 64)] == '0')
		return (0xdfbdff);
	return (0x4E1852);
}

void    draw_mini_map(t_all *all)
{
    int i;
    int j;
	unsigned int color;

	i = 0;
	while (i < TILE_SIZE * 3)
	{
		j = 0;
		while (j < TILE_SIZE * 3)
		{
			color = get_color(all, j, i);
			my_mlx_pixel_put(all, j, i, color);
			j++;
		}
		i++;
	}

	//draw player
	i = 3 * TILE_SIZE / 2 - 5;
	while (i <  3 * TILE_SIZE / 2 + 5)
	{
		j = 3 * TILE_SIZE / 2 - 5;
		while (j <  3 * TILE_SIZE / 2 + 5)
		{
			my_mlx_pixel_put(all, j, i, 0x000000);
			j++;
		}
		i++;
	}

	draw_line(all, 3 * TILE_SIZE / 2, 3 * TILE_SIZE / 2, 3 * TILE_SIZE / 2 + cos(all->player->rotation_angle) * 40, 3 * TILE_SIZE / 2 + sin(all->player->rotation_angle) * 40);
}