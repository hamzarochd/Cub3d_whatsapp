/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:58:39 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 13:35:41 by hrochd           ###   ########.fr       */
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
	free_parsing(mlx);
	exit(0);
}
