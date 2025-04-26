/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycasting_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:41:43 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/26 18:47:13 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	hwall_init(t_point *wl, t_point u_vec, t_point plr, double *scl_fac)
{
	if (u_vec.y > 0)
		wl->y = TILE_SIZE * (int)(plr.y / TILE_SIZE);
	else
		wl->y = (TILE_SIZE * ((int)(plr.y / TILE_SIZE) + 1));
	*scl_fac = (plr.y - wl->y) / u_vec.y;
	wl->x = plr.x + (*scl_fac * u_vec.x);
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

t_point	get_h_wall(t_mlx *mlx, t_point plr, double ray_angle, double *ray_l)
{
	t_point	wall_pt;
	int		found_wall;
	double	scaling_factor;
	t_point	unit_vec;
	int		delta_x_pw;

	if (ray_angle == PI || ray_angle == 0)
		return (infinite_ray(ray_l));
	vec_init(&unit_vec, ray_angle, &found_wall);
	hwall_init(&wall_pt, unit_vec, plr, &scaling_factor);
	while (!found_wall)
	{
		if (hwall_hit(unit_vec, mlx, &wall_pt))
			break ;
		scaling_factor = (plr.y - wall_pt.y) / unit_vec.y;
		wall_pt.x = plr.x + (scaling_factor * unit_vec.x);
	}
	delta_x_pw = ((wall_pt.x - plr.x) * (wall_pt.x - plr.x));
	*ray_l = sqrt(delta_x_pw + ((wall_pt.y - plr.y) * (wall_pt.y - plr.y)));
	return (wall_pt);
}
