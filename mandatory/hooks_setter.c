/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:01 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 11:59:02 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_hooks(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx_cnx, keydown_handler, mlx);
	mlx_loop_hook(mlx->mlx_cnx, render, mlx);
}
