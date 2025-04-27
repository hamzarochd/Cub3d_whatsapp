#include "cub3d.h"

void	vwall_init(t_point *wall_pt, t_point unit_vec
	, t_point player_pt, double *scaling_factor)
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

t_point	get_v_wall(t_mlx *mlx, t_point player_pt, double ray_angle
	, double *ray_lenght)
{
	t_point	wall_pt;
	int		found_wall;
	double	scaling_factor;
	t_point	unit_vec;

	if (ray_angle == PI / 2 || ray_angle == 3 * (PI / 2))
		return (infinite_ray(ray_lenght));
	vec_init(&unit_vec, ray_angle, &found_wall);
	vwall_init(&wall_pt, unit_vec, player_pt, &scaling_factor);
	while (!found_wall)
	{
		if (vwall_hit(unit_vec, mlx, &wall_pt))
			break ;
		scaling_factor = (player_pt.x - wall_pt.x) / unit_vec.x;
		wall_pt.y = player_pt.y + (scaling_factor * unit_vec.y);
	}
	*ray_lenght = sqrt(((wall_pt.x - player_pt.x) * (wall_pt.x - player_pt.x))
			+ ((wall_pt.y - player_pt.y) * (wall_pt.y - player_pt.y)));
	return (wall_pt);
}
