/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:26:22 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/27 14:34:40 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_in_wall(char **map, double x, double y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x < (mlx->map.width / TILE_SIZE)
		&& map_y < (mlx->map.height / TILE_SIZE)
		&& map_x >= 0 && map_y >= 0)
	{
		if (map[map_y][map_x] == '1' || map[map_y][map_x] == 'D')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	clamp_value(int value, int min_val, int max_val)
{
	if (value < min_val)
		return (min_val);
	if (value > max_val)
		return (max_val);
	return (value);
}

void	normalize_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	else if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

int	destroy_handler(void)
{
	exit(0);
	return (0);
}

void	*salloc(int size)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		printf("Error\nmalloc\n");
		exit(1);
	}
	return (alloc);
}
