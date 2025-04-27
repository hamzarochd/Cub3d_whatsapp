/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:58:58 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/27 10:16:48 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_north(t_mlx *mlx, t_point north)
{
	static mlx_image_t	*n;

	if (mlx->is_loading)
		return ;
	draw_filled_circle(mlx, north.x, north.y, 10);
	if (n)
		mlx_delete_image(mlx->mlx_cnx, n);
	n = mlx_put_string(mlx->mlx_cnx, "N", north.x - 5, north.y - 10);
}

void	map_put_pixel(t_mlx *mlx, char cell, int x, int y)
{
	if (cell == '0' || ft_strchr("NSEW", cell))
		mlx_put_pixel(mlx->img, x, y, rgb(211, 211, 211, 255));
	else if (cell == 'O')
		mlx_put_pixel(mlx->img, x, y, rgb(179, 158, 106, 255));
	else if (cell == 'D')
		mlx_put_pixel(mlx->img, x, y, rgb(103, 73, 40, 255));
	else
		mlx_put_pixel(mlx->img, x, y, rgb(108, 108, 108, 255));
}

int	is_in_map(t_mlx *mlx, t_minimap *mp, int dx, int dy)
{
	double	rot_x;
	double	rot_y;
	int		world_x;
	int		world_y;

	rot_x = dx * mp->cos_angle - dy * mp->sin_angle;
	rot_y = dx * mp->sin_angle + dy * mp->cos_angle;
	world_x = mlx->player.x_player + (rot_x * mp->scale);
	world_y = mlx->player.y_player + (rot_y * mp->scale);
	world_x = clamp_value(world_x, 0, mp->map_pixel_width - 1);
	world_y = clamp_value(world_y, 0, mp->map_pixel_height - 1);
	mp->tile_x = world_x / TILE_SIZE;
	mp->tile_y = world_y / TILE_SIZE;
	if (mp->tile_x < 0 || mp->tile_x >= mlx->map.width / TILE_SIZE
		|| mp->tile_y < 0 || mp->tile_y >= mlx->map.height / TILE_SIZE)
		return (0);
	else
		return (1);
}

void	minimap_init(t_mlx *mlx, t_minimap *mp)
{
	mp->scale = (double)mlx->minimap_scale;
	mp->rot_angle = mlx->player.rot_angle - (PI / 2);
	mp->map_pixel_width = mlx->map.width * TILE_SIZE;
	mp->map_pixel_height = mlx->map.height * TILE_SIZE;
	mp->north.x = MAP_X - cos(mlx->player.rot_angle) * (MAP_RADIUS);
	mp->north.y = MAP_Y - sin(mlx->player.rot_angle) * (MAP_RADIUS);
	mp->cos_angle = cos(mp->rot_angle * -1);
	mp->sin_angle = sin(mp->rot_angle * -1);
	mp->tile_x = 0;
	mp->tile_y = 0;
	mp->x = 64;
	mp->y = 64;
}

void	minimap(t_mlx *mlx)
{
	t_minimap	mp;

	minimap_init(mlx, &mp);
	draw_filled_circle(mlx, 192, 192, 135);
	while (mp.y < 320)
	{
		mp.x = 64;
		mp.dy = mp.y - MAP_Y;
		while (mp.x < 320)
		{
			mp.dx = mp.x - MAP_X;
			if ((mp.dx) * (mp.dx) + (mp.dy) * (mp.dy) < 16384)
			{
				if (is_in_map(mlx, &mp, mp.dx, mp.dy))
					map_put_pixel(mlx,
						mlx->cube->map[mp.tile_y][mp.tile_x], mp.x, mp.y);
				else
					mlx_put_pixel(mlx->img, mp.x, mp.y, rgb(0, 0, 0, 255));
			}
			mp.x++;
		}
		mp.y++;
	}
	put_north(mlx, mp.north);
}
