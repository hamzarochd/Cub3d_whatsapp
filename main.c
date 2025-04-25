#include "cub3d.h"

uint32_t	rgb(int r, int g, int b, int a)
{
	return (((r & 0xFF) << 24) | ((g & 0xFF) << 16)
		| ((b & 0xFF) << 8) | (a & 0xFF));
}



void	my_mlx_put_pixel(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}



void	draw_filled_circle(t_mlx *mlx, int x_center, int y_center, int radius)
{
	int x;
	int y;
	int color;

	color = rgb(0, 0, 0, 255);
	y = y_center - radius;
	while (y <= y_center + radius)
	{
		x = x_center - radius;
		while (x <= x_center + radius)
		{
			if ((x - x_center) * (x - x_center) + (y - y_center) * (y - y_center) <= radius * radius)
			{
				mlx_put_pixel(mlx->img, x, y, color);
			}
			x++;
		}
		y++;
	}
}





int	is_in_wall(char **map, double x, double y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x < (mlx->map.width / TILE_SIZE) && map_y < (mlx->map.height / TILE_SIZE)
		&& map_x >= 0 && map_y >= 0)
	{
		if (map[map_y][map_x] == '1' || map[map_y][map_x] == 'D')
			return (1);
		else
			return (0);
	}
	return (1);
}

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



















int clamp_value(int value, int min_val, int max_val)
{
	if (value < min_val)
		return min_val;
	if (value > max_val)
		return max_val;
	return value;
}




////////////////////////////////////////




void    re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int    index;

	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
	{
		index = (y * img->width + x) * 4;
		img->pixels[index + 3] = (color >> 24) & 0xFF; 
		img->pixels[index + 2] = (color >> 16) & 0xFF;   
		img->pixels[index + 1] = (color >> 8) & 0xFF;
		img->pixels[index + 0] = (color) & 0xFF;
	}
}

void put_wall(t_mlx *mlx, int i, int *j, t_wall wall)
{
	int k;
	uint32_t index;
	uint32_t tex_width;
	uint32_t tex_height;
	
	tex_width = wall.wall_texture->width;
	tex_height = wall.wall_texture->height;
	wall.tex.texel_x = (wall.ray->tile_hit_point) * (tex_width / TILE_SIZE);
	wall.tex.texel_x = wall.tex.texel_x % tex_width;
	index = wall.tex.texel_x;
	k = *j;
	while (k < wall.wall_end)
	{
		wall.tex.texel_y = ((int)wall.tex.tex_index) * tex_width;
		wall.tex.texel_y = wall.tex.texel_y % (tex_width * tex_height);
		index = (index + wall.tex.texel_y) % (tex_width * tex_height); 
		wall.tex.texel_color = ((uint32_t *)(wall.wall_texture->pixels))[(wall.tex.texel_y + wall.tex.texel_x)];
		re_put_pixel(mlx->img, i, k, wall.tex.texel_color);
		k++;
		wall.tex.tex_index += wall.wall_prop;
	}
	*j = k;
}


void put_ceiling(t_mlx *mlx, int i, int *j,int wall_start)
{
	int k;
	int ceiling_color;

	ceiling_color = rgb(mlx->cube->ceiling_color[0],
						mlx->cube->ceiling_color[1],
						mlx->cube->ceiling_color[2], 255);
	k = *j;
	while(k < wall_start)
	{
		mlx_put_pixel(mlx->img, i, k, ceiling_color);
		k++;
	}
	*j = k;
}

void    put_floor(t_mlx *mlx, int i, int *j)
{
	int k;
	int floor_color;

	floor_color = rgb(mlx->cube->floor_color[0],
						mlx->cube->floor_color[1],
						mlx->cube->floor_color[2], 255);
	k = *j;
	while(k < W_HEIGHT)
	{
		mlx_put_pixel(mlx->img, i, k, floor_color);
		k++;
	}
	*j = k;     
}

/////////////////////////////



void    normmalize_angle(double *angle)
{
	if(*angle < 0)
		*angle += 2*PI;
	else if (*angle > 2*PI)
		*angle -= 2*PI;
}









int	destroy_handler()
{
	exit(0);
	return (0);
}


void    mouse_handler(double xpos, double ypos, void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	const double center_x = W_WIDTH/2;
	double delta_x = xpos - center_x;

	if (mlx->is_loading)
		return ;
	mlx->player.rot_angle -= (PI/2) * (delta_x/center_x);
	if (mlx->player.rot_angle >= 2*PI)
		mlx->player.rot_angle -= 2*PI;
	if (mlx->player.rot_angle < 0)
		mlx->player.rot_angle += 2*PI;

	mlx_set_mouse_pos(mlx->mlx_cnx, W_WIDTH/2, W_HEIGHT/2);
}













void *salloc(int size)
{
	void *alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		printf("MALLOC ERROR\n");
		exit(1);
	}
	return (alloc);
}














void    animation_hook(void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	static int gun_i;
	static int fire_i;
	static int reload_i;

	handle_walking_animation(mlx, &gun_i);
	handle_firing_animation(mlx, &fire_i);
	handle_reloading_animation(mlx, &reload_i, &gun_i);
}



void set_hooks(t_mlx *mlx)
{
	mlx_set_mouse_pos(mlx->mlx_cnx, W_WIDTH/2, W_HEIGHT/2);
	mlx_loop_hook(mlx->mlx_cnx, keydown_handler, mlx);
	mlx_cursor_hook(mlx->mlx_cnx, mouse_handler, mlx);
	mlx_mouse_hook(mlx->mlx_cnx, fire_hook, mlx);
	mlx_set_cursor_mode(mlx->mlx_cnx, 0x00034003);
	mlx_key_hook(mlx->mlx_cnx, open_door, mlx);
	mlx_loop_hook(mlx->mlx_cnx, render, mlx);
	mlx_loop_hook(mlx->mlx_cnx, animation_hook, mlx);
}

int main(int ac, char **av)
{
	t_mlx   mlx;
	t_cube  cube;

	mlx.time = mlx_get_time();
	if (ac < 2)
	{
		printf("need file name !\n");
		return (1);
	}
	if (main_parsing(&cube, av))
		return (1);
	bzero(&mlx, sizeof(t_mlx));
	initializer(&mlx, &cube);
	// adjust floor color
	// printf("floor color : %d %d %d\n", mlx.cube->floor_color[0], mlx.cube->floor_color[1], mlx.cube->floor_color[2]);
	// printf("ceiling color : %d %d %d\n", mlx.cube->ceiling_color[0], mlx.cube->ceiling_color[1], mlx.cube->ceiling_color[2]);
	load_graphics(&mlx, &cube);
	put_images(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_cnx);
}
