#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"

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
		my_mlx_pixel_put(all, x * SCALE, y * SCALE, 0xff0);
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
			my_mlx_pixel_put(all, (all->player->coor.x + j) * SCALE , (all->player->coor.y+ i) * SCALE, 0x005599);
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
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (character == '0' || character == 'N')
				my_mlx_pixel_put(all, (posx + j) * SCALE, (posy + i) * SCALE, 0x99ff99);
			else if (character == '1')
				my_mlx_pixel_put(all, (posx + j) * SCALE, (posy + i) * SCALE, 0x00aaa0);
			j++;
		}
		i++;
	}
}

void    draw_mini_map(t_all *all)
{
    int i = 0;
    int j = 0;
    static int flag = 1;
    while (i < 7)
	{
		j = 0;
		while (j < (int)ft_strlen(all->map[i]))
		{
            // if (all->map[i][j] && all->map[i][j] == 'N' && flag)
            // {
            //     flag = 0;
            //     all->player->coor.x = j * 64;
            //     all->player->coor.y = i * 64;
			// 	all->player->rotation_angle = 0 * M_PI;
            // }
			draw_squar(all, j * 64, i * 64, all->map[i][j]);
			j++;
		}
		i++;
	}
    draw_player(all);
	draw_line(all, all->player->coor.x, all->player->coor.y, all->rays[0].coor.x, all->rays[0].coor.y);

}