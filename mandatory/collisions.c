#include "cub3d.h"

int	check_diagonal(char **map, int xtile, int ytile, t_mlx *mlx)
{
	int	player_x;
	int	player_y;

	player_x = mlx->player.x_player / TILE_SIZE;
	player_y = mlx->player.y_player / TILE_SIZE;
	if ((map[player_y][xtile] == '1' && map[ytile][player_x] == '1') ||
		(map[player_y][xtile] == 'D' && map[ytile][player_x] == 'D'))
		return (1);
	return (0);
}

void	calculate_movement(t_mlx *mlx, char direction, double *x, double *y)
{
	if (direction == 'U')
	{
		*x += cos(mlx->player.rot_angle) * (SPEED + 200);
		*y -= sin(mlx->player.rot_angle) * (SPEED + 200);
	}
	else if (direction == 'D')
	{
		*x -= cos(mlx->player.rot_angle) * (SPEED + 200);
		*y += sin(mlx->player.rot_angle) * (SPEED + 200);
	}
	else if (direction == 'L')
	{
		*x += cos(mlx->player.rot_angle + PI / 2) * (SPEED + 200);
		*y -= sin(mlx->player.rot_angle + PI / 2) * (SPEED + 200);
	}
	else if (direction == 'R')
	{
		*x += cos(mlx->player.rot_angle - PI / 2) * (SPEED + 200);
		*y -= sin(mlx->player.rot_angle - PI / 2) * (SPEED + 200);
	}
}

int	handle_wall_collision(t_mlx *mlx, double x, double y)
{
	if (is_in_wall(mlx->cube->map, x, y, mlx))
	{
		if (!is_in_wall(mlx->cube->map, x, mlx->player.y_player, mlx))
			mlx->player.x_player += (x - mlx->player.x_player) / 2;
		if (!is_in_wall(mlx->cube->map, mlx->player.x_player, y, mlx))
			mlx->player.y_player += (y - mlx->player.y_player) / 2;
		return (1);
	}
	return (0);
}

int	check_wall(t_mlx *mlx, char direction)
{
	double	x;
	double	y;
	double	old_x;
	double	old_y;

	old_x = mlx->player.x_player;
	old_y = mlx->player.y_player;
	x = mlx->player.x_player;
	y = mlx->player.y_player;
	calculate_movement(mlx, direction, &x, &y);
	if (handle_wall_collision(mlx, x, y))
		return (1);
	if (old_x / TILE_SIZE != x / TILE_SIZE && old_y / TILE_SIZE != y
		/ TILE_SIZE)
		return (check_diagonal(mlx->cube->map, x / TILE_SIZE, y
				/ TILE_SIZE, mlx));
	return (0);
}
