/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycasting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:07 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 11:59:08 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hwall_init(t_point *wall_pt, t_point unit_vec, t_point player_pt
		, double *scaling_factor)
{
	if (unit_vec.y > 0)
		wall_pt->y = TILE_SIZE * (int)(player_pt.y / TILE_SIZE);
	else
		wall_pt->y = (TILE_SIZE * ((int)(player_pt.y / TILE_SIZE) + 1));
	*scaling_factor = (player_pt.y - wall_pt->y) / unit_vec.y;
	wall_pt->x = player_pt.x + (*scaling_factor * unit_vec.x);
}

int	hwall_hit(t_point unit_vec, t_mlx *mlx, t_point *wall_pt)
{
	if (unit_vec.y > 0)
	{
		if (is_in_wall(mlx->cube->map, wall_pt->x, wall_pt->y - 1, mlx))
			return (1);
		wall_pt->y -= TILE_SIZE;
	}
	else
	{
		if (is_in_wall(mlx->cube->map, wall_pt->x, wall_pt->y + 1, mlx))
			return (1);
		wall_pt->y += TILE_SIZE;
	}
	return (0);
}

t_point	get_h_wall(t_mlx *mlx, t_point player_pt, double ray_angle
		, double *ray_lenght)
{
	t_point	wall_pt;
	int		found_wall;
	double	scaling_factor;
	t_point	unit_vec;

	if (ray_angle == PI || ray_angle == 0)
		return (infinite_ray(ray_lenght));
	vec_init(&unit_vec, ray_angle, &found_wall);
	hwall_init(&wall_pt, unit_vec, player_pt, &scaling_factor);
	while (!found_wall)
	{
		if (hwall_hit(unit_vec, mlx, &wall_pt))
			break ;
		scaling_factor = (player_pt.y - wall_pt.y) / unit_vec.y;
		wall_pt.x = player_pt.x + (scaling_factor * unit_vec.x);
	}
	*ray_lenght = sqrt(((wall_pt.x - player_pt.x) * (wall_pt.x - player_pt.x))
			+ ((wall_pt.y - player_pt.y) * (wall_pt.y - player_pt.y)));
	return (wall_pt);
}
