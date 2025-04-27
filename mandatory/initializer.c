/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:09 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 14:34:23 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_infos(t_cube *cube, int *p_x, int *p_y, char *p_or)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cube->map[i])
	{
		j = 0;
		while (cube->map[i][j])
		{
			if (cube->map[i][j] == 'N' || cube->map[i][j] == 'S'
				|| cube->map[i][j] == 'E' || cube->map[i][j] == 'W')
			{
				*p_x = j;
				*p_y = i;
				*p_or = cube->map[i][j];
			}
			j++;
		}
		i++;
	}
}

void	player_init(t_mlx *mlx)
{
	int		player_x;
	int		player_y;
	char	player_orientation;

	player_x = 0;
	player_y = 0;
	player_orientation = '0';
	if (!mlx || !mlx->cube->map)
	{
		printf("Error\nInit Error\n");
		return ;
	}
	player_infos(mlx->cube, &player_x, &player_y, &player_orientation);
	mlx->player.x_player = (TILE_SIZE * player_x) + (TILE_SIZE / 2);
	mlx->player.y_player = (TILE_SIZE * player_y) + (TILE_SIZE / 2);
	if (player_orientation == 'N')
		mlx->player.rot_angle = PI / 2;
	else if (player_orientation == 'W')
		mlx->player.rot_angle = PI;
	else if (player_orientation == 'S')
		mlx->player.rot_angle = (3 * PI) / 2;
	else if (player_orientation == 'E')
		mlx->player.rot_angle = 0;
}

void	set_dimensions(t_cube *cube, int *height_tiles, int *width_tiles)
{
	int	i;
	int	h;
	int	w;

	i = 0;
	h = 0;
	w = 0;
	while (cube->map[i])
	{
		if (ft_strlen(cube->map[i]) > w)
			w = ft_strlen(cube->map[i]);
		i++;
	}
	h = i;
	*height_tiles = h;
	*width_tiles = w;
}

void	initializer(t_mlx *mlx, t_cube *cube)
{
	int	h_tiles;
	int	w_tiles;

	set_dimensions(cube, &h_tiles, &w_tiles);
	mlx->mlx_cnx = mlx_init(W_WIDTH, W_HEIGHT, "CUB3D", false);
	if (!mlx->mlx_cnx)
		ft_exit(mlx);
	mlx->is_loading = 1;
	mlx->img = mlx_new_image(mlx->mlx_cnx, W_WIDTH, W_HEIGHT);
	if (!mlx->img)
		ft_exit(mlx);
	mlx->map.height = h_tiles * TILE_SIZE;
	mlx->map.width = w_tiles * TILE_SIZE;
	mlx->cube = cube;
	mlx->wall_const = (W_HEIGHT / 5) * ((W_HEIGHT / 10) * 80);
	player_init(mlx);
}
