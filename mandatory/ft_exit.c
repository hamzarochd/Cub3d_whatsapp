/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:58:39 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 11:31:13 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	ft_exit(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	delete_images(mlx);
	if (mlx->mlx_cnx)
	{
		mlx_close_window(mlx->mlx_cnx);
		mlx_terminate(mlx->mlx_cnx);
	}
	safe_malloc(-1);
	exit(0);
}
