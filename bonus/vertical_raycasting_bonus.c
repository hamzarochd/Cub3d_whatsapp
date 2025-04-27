/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycasting_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:34:12 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/27 10:20:16 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vwall_init(t_point *wall_pt, t_point unit_vec,
		t_point player_pt, double *scaling_factor)
{
	if (unit_vec.x < 0)
		wall_pt->x = TILE_SIZE * (int)(player_pt.x / TILE_SIZE);
	else
		wall_pt->x = (TILE_SIZE * ((int)(player_pt.x / TILE_SIZE) + 1));
	*scaling_factor = (player_pt.x - wall_pt->x) / unit_vec.x;
	wall_pt->y = player_pt.y + (*scaling_factor * unit_vec.y);
}

int	vwall_hit(t_point unit_vec, t_mlx *mlx, t_point *wall_pt)
{
	if (unit_vec.x > 0)
	{
		if (is_in_wall(mlx->cube->map, wall_pt->x + 1, wall_pt->y, mlx))
			return (1);
		wall_pt->x += TILE_SIZE;
	}
	else
	{
		if (is_in_wall(mlx->cube->map, wall_pt->x - 1, wall_pt->y, mlx))
			return (1);
		wall_pt->x -= TILE_SIZE;
	}
	return (0);
}

t_point	get_v_wall(t_mlx *mlx, t_point plr,
		double ray_angle, double *ray_l)
{
	t_point	wall_pt;
	int		found_wall;
	double	scaling_factor;
	t_point	unit_vec;
	double	delta_x_pw;

	if (ray_angle == PI / 2 || ray_angle == 3 * (PI / 2))
		return (infinite_ray(ray_l));
	vec_init(&unit_vec, ray_angle, &found_wall);
	vwall_init(&wall_pt, unit_vec, plr, &scaling_factor);
	while (!found_wall)
	{
		if (vwall_hit(unit_vec, mlx, &wall_pt))
			break ;
		scaling_factor = (plr.x - wall_pt.x) / unit_vec.x;
		wall_pt.y = plr.y + (scaling_factor * unit_vec.y);
	}
	delta_x_pw = (wall_pt.x - plr.x) * (wall_pt.x - plr.x);
	*ray_l = sqrt(delta_x_pw + ((wall_pt.y - plr.y) * (wall_pt.y - plr.y)));
	return (wall_pt);
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;	
	size_t	i;

	i = 0;
	ptr = salloc(number * size);
	while (i < number)
	{
		*(char *)(ptr + 1) = '\0';
		i++;
	}
	return (ptr);
}

int	ft_strcmp(char	*s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
