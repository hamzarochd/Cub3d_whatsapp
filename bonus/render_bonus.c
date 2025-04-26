#include "cub3d_bonus.h"


mlx_image_t *define_wall_tex(int is_door, char wall_orientation, t_graphics graphics)
{
	if (is_door)
		return (graphics.door_txtr);
	else
	{
		if (wall_orientation == 'N')
			return (graphics.no_txtr);
		else if (wall_orientation == 'S')
			return (graphics.so_txtr);
		else if (wall_orientation == 'E')
			return (graphics.ea_txtr);
		else 
			return (graphics.we_txtr);
	}
}

t_wall  get_wall(t_mlx *mlx, t_ray *ray, double ray_pixels)
{
	t_wall wall;
	
	wall.wall_start = (W_HEIGHT - ray_pixels) / 2;
	wall.wall_end = wall.wall_start + ray_pixels;
	wall.wall_prop = W_HEIGHT / (double)ray_pixels;
	wall.wall_texture = define_wall_tex(ray->is_door, ray->wall_orientation, mlx->graphics);  
	wall.tex.tex_index = 0;
	return (wall);
}

void    set_render_var(t_mlx **mlx, t_point *player_pt, void *param, t_rendex *r)
{
	double current_time;

	*mlx = (t_mlx *)param;
	player_pt->x = (*mlx)->player.x_player;
	player_pt->y = (*mlx)->player.y_player;
	r->angle_start = (*mlx)->player.rot_angle + PI/6;
	normalize_angle(&(r->angle_start));
	r->i = 0;
	current_time = mlx_get_time();
	if (current_time > (*mlx)->time + 7 &&
		current_time < (*mlx)->time + 8)
	{
		(*mlx)->graphics.loading_img->instances[0].enabled = false;
		(*mlx)->is_loading = 0;
		if ((*mlx)->img->instances[0].enabled == false)
			(*mlx)->img->instances[0].enabled = true;
		(*mlx)->graphics.gun->instances[0].enabled = true;
		(*mlx)->graphics.player->instances[0].enabled = true;
	}
}

void    set_ray(t_ray *ray, t_mlx *mlx, t_point player_pt, t_rendex *r)
{
	*ray = calculate_ray_lenght(mlx, player_pt, r->angle_start);
	ray->delta_angle = r->angle_start - mlx->player.rot_angle;
	ray->ray_pixels = mlx->wall_const / (ray->ray_length * cos(ray->delta_angle));
	r->j = 0;
}


void render(void   *param)
{
	t_mlx   *mlx;
	t_ray   ray;
	t_point player_pt;
	t_rendex    r;
	t_wall wall;

	set_render_var(&mlx, &player_pt, param, &r);
	while (r.i < W_WIDTH && !mlx->is_loading)
	{
		set_ray(&ray, mlx, player_pt, &r);
		wall = get_wall(mlx, &ray, ray.ray_pixels);
		put_ceiling(mlx, r.i, &r.j, wall.wall_start);
		if (ray.ray_pixels > W_HEIGHT)
		{
			wall.tex.tex_index = (-wall.wall_start) * wall.wall_prop;
			r.j = 0;
		}
		wall.ray = &ray;
		put_wall(mlx, r.i, &r.j, wall);
		put_floor(mlx, r.i, &r.j);
		r.angle_start -= (PI/3) / W_WIDTH;
		normalize_angle(&r.angle_start);
		r.i++;
	}
	minimap(mlx);
}