/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reloading_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:22:31 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/26 19:24:57 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	reload_animation(t_mlx *mlx, int x, int y)
{
	int	i;
	int	src;
	int	dest;

	i = 0;
	src = (x * RLD_W) + ((y * RELOAD_H) * mlx->graphics.reload_tex->width);
	dest = 0;
	while (i < RELOAD_H)
	{
		memcpy(((uint32_t *) mlx->graphics.reload->pixels) + dest,
			((uint32_t *) mlx->graphics.reload_tex->pixels) + src, RLD_W * 4);
		src += mlx->graphics.reload_tex->width;
		dest += RLD_W;
		i++;
	}
}

void	handle_reloading_animation(t_mlx *mlx, int *reload_i, int *gun_i)
{
	if (mlx->is_reloading && !mlx->is_loading)
	{
		if (*reload_i == 0)
		{
			mlx->graphics.gun->instances[0].enabled = false;
			mlx->graphics.reload->instances[0].enabled = true;
			mlx->graphics.fire->instances[0].enabled = false;
		}
		reload_animation(mlx, *reload_i % 8, *reload_i / 8);
		(*reload_i)++;
		if (*reload_i == 44)
		{
			*reload_i = 0;
			mlx->is_reloading = 0;
			mlx->graphics.reload->instances[0].enabled = false;
			mlx->graphics.gun->instances[0].enabled = true;
			*gun_i = 0;
		}
	}
}
