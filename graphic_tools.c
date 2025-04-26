#include "cub3d.h"



uint32_t	rgb(int r, int g, int b, int a)
{
	return (((r & 0xFF) << 24) | ((g & 0xFF) << 16)
		| ((b & 0xFF) << 8) | (a & 0xFF));
}



void	my_mlx_put_pixel(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}



void	draw_filled_circle(t_mlx *mlx, int x_center, int y_center, int radius)
{
	int x;
	int y;
	int color;

	color = rgb(0, 0, 0, 255);
	y = y_center - radius;
	while (y <= y_center + radius)
	{
		x = x_center - radius;
		while (x <= x_center + radius)
		{
			if ((x - x_center) * (x - x_center) + (y - y_center) * (y - y_center) <= radius * radius)
			{
				mlx_put_pixel(mlx->img, x, y, color);
			}
			x++;
		}
		y++;
	}
}