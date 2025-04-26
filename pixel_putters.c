#include "cub3d.h"


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