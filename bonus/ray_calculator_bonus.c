#include "cub3d_bonus.h"


int	is_in_door(char **map, double x, double y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x < (mlx->map.width / TILE_SIZE) && map_y < (mlx->map.height / TILE_SIZE)
		&& map_x >= 0 && map_y >= 0)
	{
		if (map[map_y][map_x] == 'D')
			return (1);
		else
			return (0);
	}
	return (0);
}

void    get_hray(t_mlx *mlx, t_ray *ray, t_point wall_pt)
{
	char **map;

	map = mlx->cube->map;
	ray->tile_hit_point = (int)wall_pt.x % TILE_SIZE;
	if (ray->wall_orientation == 'S')
		ray->tile_hit_point = TILE_SIZE - ray->tile_hit_point;
	if ((ray->wall_orientation == 'N' && is_in_door(map, wall_pt.x, wall_pt.y - 1, mlx))
		|| (ray->wall_orientation == 'S' && is_in_door(map, wall_pt.x, wall_pt.y + 1, mlx)))
		ray->is_door = 1;
}


void    get_vray(t_mlx *mlx, t_ray *ray, t_point wall_pt)
{
	char **map;

	map = mlx->cube->map;
	ray->tile_hit_point = (int)wall_pt.y % TILE_SIZE;
		if (ray->wall_orientation == 'W')
			ray->tile_hit_point = TILE_SIZE - ray->tile_hit_point;
		if ((ray->wall_orientation == 'W' && is_in_door(map, wall_pt.x - 1, wall_pt.y, mlx))
			|| (ray->wall_orientation == 'E' && is_in_door(map, wall_pt.x + 1, wall_pt.y, mlx)))
			ray->is_door = 1;
}

char    get_wall_orientation(double angle, int is_wall_horizontal)
{
	char wall_orientation;

	if (is_wall_horizontal)
	{
		if (angle < PI)
			wall_orientation = 'N';
		else
			wall_orientation = 'S';
	}
	else
	{
		if (angle < (3*PI)/2 && angle > PI/2)
			wall_orientation = 'W';
		else
			wall_orientation = 'E';
	}
	return (wall_orientation);
}

t_ray calculate_ray_lenght(t_mlx *mlx, t_point player_pt, double angle)
{
	t_point h_wall;
	t_point v_wall;
	double  v_ray;
	double  h_ray;
	t_ray   ray;

	h_wall = get_h_wall(mlx, player_pt, angle, &h_ray);
	v_wall = get_v_wall(mlx, player_pt, angle, &v_ray);
	ray.is_door = 0;
	ray.ray_pixels = 0;
	if (h_ray < v_ray)
	{
		ray.wall_orientation = get_wall_orientation(angle, 1);
		ray.ray_length = h_ray;
		get_hray(mlx, &ray, h_wall);
		return ray;
	}
	else
	{
		ray.wall_orientation = get_wall_orientation(angle, 0);
		ray.ray_length = v_ray;
		get_vray(mlx, &ray, v_wall);
		return ray;
	}
}