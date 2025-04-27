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
