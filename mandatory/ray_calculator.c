/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:32 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 11:59:33 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_hray(t_ray *ray, t_point wall_pt)
{
	ray->tile_hit_point = (int)wall_pt.x % TILE_SIZE;
	if (ray->wall_orientation == 'S')
		ray->tile_hit_point = TILE_SIZE - ray->tile_hit_point;
}

void	get_vray(t_ray *ray, t_point wall_pt)
{
	ray->tile_hit_point = (int)wall_pt.y % TILE_SIZE;
	if (ray->wall_orientation == 'W')
		ray->tile_hit_point = TILE_SIZE - ray->tile_hit_point;
}

char	get_wall_orientation(double angle, int is_wall_horizontal)
{
	char	wall_orientation;

	if (is_wall_horizontal)
	{
		if (angle < PI)
			wall_orientation = 'N';
		else
			wall_orientation = 'S';
	}
	else
	{
		if (angle < (3 * PI) / 2 && angle > PI / 2)
			wall_orientation = 'W';
		else
			wall_orientation = 'E';
	}
	return (wall_orientation);
}

t_ray	calculate_ray_lenght(t_mlx *mlx, t_point player_pt, double angle)
{
	t_point	h_wall;
	t_point	v_wall;
	double	v_ray;
	double	h_ray;
	t_ray	ray;

	h_wall = get_h_wall(mlx, player_pt, angle, &h_ray);
	v_wall = get_v_wall(mlx, player_pt, angle, &v_ray);
	ray.ray_pixels = 0;
	if (h_ray < v_ray)
	{
		ray.wall_orientation = get_wall_orientation(angle, 1);
		ray.ray_length = h_ray;
		get_hray(&ray, h_wall);
		return (ray);
	}
	else
	{
		ray.wall_orientation = get_wall_orientation(angle, 0);
		ray.ray_length = v_ray;
		get_vray(&ray, v_wall);
		return (ray);
	}
}
