/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:56:24 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/26 18:58:23 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_player(t_mlx *mlx, char direction, int *speed)
{
	if (check_wall(mlx, direction))
		return ;
	if (direction == 'U')
	{
		mlx->player.x_player += cos(mlx->player.rot_angle) * (*speed);
		mlx->player.y_player -= sin(mlx->player.rot_angle) * (*speed);
	}
	else if (direction == 'D')
	{
		mlx->player.x_player -= cos(mlx->player.rot_angle) * (*speed);
		mlx->player.y_player += sin(mlx->player.rot_angle) * (*speed);
	}
	else if (direction == 'L')
	{
		mlx->player.x_player += cos(mlx->player.rot_angle + PI / 2) * (*speed);
		mlx->player.y_player -= sin(mlx->player.rot_angle + PI / 2) * (*speed);
	}
	else if (direction == 'R')
	{
		mlx->player.x_player += cos(mlx->player.rot_angle - PI / 2) * (*speed);
		mlx->player.y_player -= sin(mlx->player.rot_angle - PI / 2) * (*speed);
	}
}

void	handle_movement_keys(t_mlx *mlx, int *speed, int *moved)
{
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_A))
	{
		move_player(mlx, 'L', speed);
		*moved = 1;
	}
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_W))
	{
		move_player(mlx, 'U', speed);
		*moved = 1;
	}
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_D))
	{
		move_player(mlx, 'R', speed);
		*moved = 1;
	}
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_S))
	{
		move_player(mlx, 'D', speed);
		*moved = 1;
	}
}

void	handle_rotation_keys(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_LEFT))
	{
		mlx->player.rot_angle += PI / 36;
		if (mlx->player.rot_angle >= 2 * PI)
			mlx->player.rot_angle -= 2 * PI;
	}
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_RIGHT))
	{
		mlx->player.rot_angle -= PI / 36;
		if (mlx->player.rot_angle < 0)
			mlx->player.rot_angle += 2 * PI;
	}
}

void	keydown_handler(void *param)
{
	t_mlx	*mlx;
	int		speed;
	int		moved;

	moved = 0;
	speed = SPEED;
	mlx = (t_mlx *)param;
	mlx->minimap_scale = MINIMAP_SCALE;
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_LEFT_SHIFT))
	{
		speed = 400;
		mlx->minimap_scale = MINIMAP_SCALE * 1.75;
	}
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_ESCAPE))
		destroy_handler();
	if (mlx->is_loading)
		return ;
	handle_movement_keys(mlx, &speed, &moved);
	handle_rotation_keys(mlx);
	if (moved)
		mlx->is_walking = 1;
	else
		mlx->is_walking = 0;
}
