/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_loader_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:34:56 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/26 19:24:57 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_images(t_mlx *mlx)
{
	int32_t	anmtn_x;

	anmtn_x = 3 * (W_WIDTH / 5);
	mlx_image_to_window(mlx->mlx_cnx, mlx->img, 0, 0);
	mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.loading_img, 0, 0);
	mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.gun,
		anmtn_x - GUN_W / 2, W_HEIGHT - GUN_H);
	mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.fire,
		anmtn_x - FIRE_W / 2, W_HEIGHT - FIRE_H);
	mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.reload,
		anmtn_x - RLD_W / 2, W_HEIGHT - RELOAD_H);
	mlx_image_to_window(mlx->mlx_cnx,
		mlx->graphics.player, MAP_X - 10, MAP_Y - 10);
	mlx->img->instances[0].enabled = false;
	mlx->graphics.gun->instances[0].enabled = false;
	gun_animation(mlx, 0, 0);
	mlx->graphics.reload->instances[0].enabled = false;
	mlx->graphics.fire->instances[0].enabled = false;
	mlx->graphics.loading_img->instances[0].enabled = true;
	mlx->graphics.player->instances[0].enabled = false;
}

mlx_image_t	*textures_loader(t_mlx *mlx, const char *path)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*img;

	tmp = mlx_load_png(path);
	if (!tmp)
		ft_exit(mlx);
	img = mlx_texture_to_image(mlx->mlx_cnx, tmp);
	if (!img)
		ft_exit(mlx);
	mlx_delete_texture(tmp);
	return (img);
}

void	load_graphics(t_mlx *mlx, t_cube *cube)
{
	mlx->graphics.no_txtr = textures_loader(mlx, cube->no_tex);
	mlx->graphics.so_txtr = textures_loader(mlx, cube->so_tex);
	mlx->graphics.ea_txtr = textures_loader(mlx, cube->ea_tex);
	mlx->graphics.we_txtr = textures_loader(mlx, cube->we_tex);
	mlx->graphics.door_txtr = textures_loader(mlx, "textures/door.png");
	mlx->graphics.sky_image = textures_loader(mlx, "textures/sky5.png");
	mlx->graphics.player = textures_loader(mlx, "textures/player_arrow1.png");
	mlx->graphics.loading_img = textures_loader(mlx, "textures/loading.png");
	mlx->graphics.fire_tex = mlx_load_png("textures/fire_tex.png");
	mlx->graphics.reload_tex = mlx_load_png("textures/reload_tex.png");
	mlx->graphics.gun_tex = mlx_load_png("textures/gun_tex.png");
	mlx->graphics.gun = mlx_new_image(mlx->mlx_cnx, GUN_W, GUN_H);
	mlx->graphics.fire = mlx_new_image(mlx->mlx_cnx, FIRE_W, FIRE_H);
	mlx->graphics.reload = mlx_new_image(mlx->mlx_cnx, RLD_W, RELOAD_H);
	if (!mlx->graphics.fire_tex || !mlx->graphics.gun_tex
		|| !mlx->graphics.reload_tex || !mlx->graphics.fire
		|| !mlx->graphics.gun || !mlx->graphics.reload
		|| !mlx->graphics.loading_img)
		ft_exit(mlx);
	mlx_resize_image(mlx->graphics.no_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.so_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.ea_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.we_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.door_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.player, 20, 20);
}
