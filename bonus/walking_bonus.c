#include "cub3d_bonus.h"


void    gun_animation(t_mlx *mlx, int x, int y)
{
	int i;
	int src;
	int dest;

	i = 0;
	src = (x * GUN_W) + ((y * GUN_H) * mlx->graphics.gun_tex->width);
	dest = 0; 

	while (i < GUN_H)
	{
		memcpy((uint32_t *)mlx->graphics.gun->pixels + dest, (uint32_t *)mlx->graphics.gun_tex->pixels + src, GUN_W * 4);
		src += mlx->graphics.gun_tex->width;
		dest += GUN_W;
		i++;
	} 
}

void	handle_walking_animation(t_mlx *mlx, int *gun_i)
{
	if (mlx->is_walking)
	{
		if (*gun_i == 0)
		{
			mlx->graphics.gun->instances[0].enabled = true;
			mlx->graphics.reload->instances[0].enabled = false;
			mlx->graphics.fire->instances[0].enabled = false;
		}
		gun_animation(mlx, *gun_i % 8, *gun_i / 8);
		(*gun_i)++;
		if (*gun_i == 44)
			*gun_i = 0;
	}
}
