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