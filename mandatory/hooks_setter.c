/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:01 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 13:31:20 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_hooks(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx_cnx, keydown_handler, mlx);
	mlx_close_hook(mlx->mlx_cnx, ft_exit, mlx);
	mlx_loop_hook(mlx->mlx_cnx, render, mlx);
}
