/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tools_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:22:04 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/27 10:20:22 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vec_init(t_point *unit_vec, double ray_angle, int *found_wall)
{
	unit_vec->x = cos(ray_angle);
	unit_vec->y = sin(ray_angle);
	*found_wall = 0;
}

t_point	infinite_ray(double *ray_lenght)
{
	t_point	inf_ray;

	inf_ray.x = INT_MAX;
	inf_ray.y = INT_MAX;
	*ray_lenght = INT_MAX;
	return (inf_ray);
}

void	ft_bzero(void	*s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
