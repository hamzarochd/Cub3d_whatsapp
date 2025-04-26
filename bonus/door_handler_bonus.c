#include "cub3d_bonus.h"


void handle_north_door(char **map, int player_x, int player_y)
{
	if (map[player_y - 1][player_x] == 'D')
		map[player_y - 1][player_x] = 'O';
	else if (map[player_y - 1][player_x] == 'O')
		map[player_y - 1][player_x] = 'D';
}

void handle_west_door(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x - 1] == 'D')
		map[player_y][player_x - 1] = 'O';
	else if (map[player_y][player_x - 1] == 'O')
		map[player_y][player_x - 1] = 'D';
}

void handle_south_door(char **map, int player_x, int player_y)
{
	if (map[player_y + 1][player_x] == 'D')
		map[player_y + 1][player_x] = 'O';
	else if (map[player_y + 1][player_x] == 'O')
		map[player_y + 1][player_x] = 'D';
}

void handle_east_door(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x + 1] == 'D')
		map[player_y][player_x + 1] = 'O';
	else if (map[player_y][player_x + 1] == 'O')
		map[player_y][player_x + 1] = 'D';
}

void    open_door(struct mlx_key_data keydata, void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	char **map = mlx->cube->map;
	int player_x = mlx->player.x_player / TILE_SIZE;
	int player_y = mlx->player.y_player / TILE_SIZE;

	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (mlx->player.rot_angle >= PI/4 && mlx->player.rot_angle < 3*(PI/4))
			handle_north_door(map, player_x, player_y);
		else if (mlx->player.rot_angle >= 3*(PI/4) && mlx->player.rot_angle < 5*(PI/4))
			handle_west_door(map, player_x, player_y);
		else if (mlx->player.rot_angle >= 5*(PI/4) && mlx->player.rot_angle < 7*(PI/4))
			handle_south_door(map, player_x, player_y);
		else
			handle_east_door(map, player_x, player_y);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		mlx->is_reloading = 1;
}