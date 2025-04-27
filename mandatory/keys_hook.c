#include "cub3d.h"

void	move_player(t_mlx *mlx, char direction)
{
	if (check_wall(mlx, direction))
		return ;
	if (direction == 'U')
	{
		mlx->player.x_player += cos(mlx->player.rot_angle) * SPEED;
		mlx->player.y_player -= sin(mlx->player.rot_angle) * SPEED;
	}
	else if (direction == 'D')
	{
		mlx->player.x_player -= cos(mlx->player.rot_angle) * SPEED;
		mlx->player.y_player += sin(mlx->player.rot_angle) * SPEED;
	}
	else if (direction == 'L')
	{
		mlx->player.x_player += cos(mlx->player.rot_angle + PI / 2) * SPEED;
		mlx->player.y_player -= sin(mlx->player.rot_angle + PI / 2) * SPEED;
	}
	else if (direction == 'R')
	{
		mlx->player.x_player += cos(mlx->player.rot_angle - PI / 2) * SPEED;
		mlx->player.y_player -= sin(mlx->player.rot_angle - PI / 2) * SPEED;
	}
}

void	handle_movement_keys(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_A))
		move_player(mlx, 'L');
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_W))
		move_player(mlx, 'U');
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_D))
		move_player(mlx, 'R');
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_S))
		move_player(mlx, 'D');
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

	mlx = (t_mlx *)param;
	if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_ESCAPE))
		destroy_handler();
	if (mlx->is_loading)
		return ;
	handle_movement_keys(mlx);
	handle_rotation_keys(mlx);
}
