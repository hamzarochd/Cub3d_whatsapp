/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:23:44 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/26 18:24:26 by hrochd           ###   ########.fr       */
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
	if (mlx->graphics.sky_image)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.sky_image);
	if (mlx->graphics.player)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.player);
	if (mlx->graphics.gun)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.gun);
	if (mlx->graphics.fire)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.fire);
	if (mlx->graphics.reload)
		mlx_delete_image(mlx->mlx_cnx, mlx->graphics.reload);
}

void	free_parsing(t_mlx *mlx)
{
	int	i;

	free(mlx->cube->file_name);
	free(mlx->cube->no_tex);
	free(mlx->cube->so_tex);
	free(mlx->cube->we_tex);
	free(mlx->cube->ea_tex);
	i = 0;
	while (mlx->cube->map[i])
		free(mlx->cube->map[i++]);
	free(mlx->cube->map);
}

void	ft_exit(t_mlx *mlx)
{
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
	free_parsing(mlx);
	exit(0);
}
