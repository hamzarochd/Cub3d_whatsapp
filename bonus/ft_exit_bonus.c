/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:23:44 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/29 13:29:13 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delete_images(t_mlx *mlx)
{
	if (mlx->graphics.no_txtr)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.no_txtr);
	if (mlx->graphics.so_txtr)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.so_txtr);
	if (mlx->graphics.ea_txtr)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.ea_txtr);
	if (mlx->graphics.we_txtr)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.we_txtr);
	if (mlx->graphics.door_txtr)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.door_txtr);
	if (mlx->graphics.player)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.player);
	if (mlx->graphics.gun)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.gun);
	if (mlx->graphics.fire)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.fire);
	if (mlx->graphics.reload)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.reload);
	if (mlx->graphics.loading_img)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.loading_img);
}

void	ft_exit(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	delete_images(mlx);
	if (mlx->graphics.gun_tex)
		mlx_delete_texture(mlx->graphics.gun_tex);
	if (mlx->graphics.fire_tex)
		mlx_delete_texture(mlx->graphics.fire_tex);
	if (mlx->graphics.reload_tex)
		mlx_delete_texture(mlx->graphics.reload_tex);
	if (mlx->mlx_cnx)
	{
		mlx_close_window(mlx->mlx_cnx);
		mlx_terminate(mlx->mlx_cnx);
	}
	safe_malloc(-1);
	exit(0);
}
