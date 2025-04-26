#include "cub3d.h"

void    fire_animation(t_mlx *mlx, int x, int y)
{
	int i;
	int src;
	int dest;

	i = 0;
	src = (x * FIRE_W) + ((y * FIRE_H) * mlx->graphics.fire_tex->width);
	dest = 0; 
	while (i < FIRE_H)
	{
		memcpy((uint32_t *)mlx->graphics.fire->pixels + dest, (uint32_t *)mlx->graphics.fire_tex->pixels + src, FIRE_W * 4);
		src += mlx->graphics.fire_tex->width;
		dest += FIRE_W;
		i++;
	} 
}

void    fire_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx->is_firing = 1;
		mlx->is_holding = 1;
	}
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		mlx->is_firing = 0;
		mlx->is_holding = 0;
	}
}



void handle_firing_animation(t_mlx *mlx, int *fire_i)
{
	if (mlx->is_firing || *fire_i != 0 || mlx->is_holding)
	{
		if (mlx->is_firing && *fire_i)
			*fire_i = 0;
		if (*fire_i == 0)
		{
			mlx->graphics.gun->instances[0].enabled = false;
			mlx->graphics.reload->instances[0].enabled = false;
			mlx->graphics.fire->instances[0].enabled = true;
			mlx->is_firing = 0;
		}
		fire_animation(mlx, *fire_i % 6, *fire_i / 6);
		*fire_i += 2;
		if (*fire_i == 16)
		{
			*fire_i = 0;
			mlx->is_firing = 0;
			mlx->graphics.fire->instances[0].enabled = false;
			mlx->graphics.gun->instances[0].enabled = true;
		}
	}
}