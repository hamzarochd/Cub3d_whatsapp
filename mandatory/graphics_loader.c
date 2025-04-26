#include "cub3d.h"


void put_images(t_mlx *mlx)
{
	mlx_image_to_window(mlx->mlx_cnx, mlx->img, 0, 0);
	mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.loading_img, 0, 0);
	mlx->img->instances[0].enabled = false;
	mlx->graphics.loading_img->instances[0].enabled = true;
}

mlx_image_t *textures_loader(t_mlx *mlx, const char *path)
{
	mlx_texture_t * tmp;
	mlx_image_t *img; 

	tmp =  mlx_load_png(path);
	if (!tmp)
		ft_exit(mlx);
	img = mlx_texture_to_image(mlx->mlx_cnx, tmp);
	if (!img)
		ft_exit(mlx);
	mlx_delete_texture(tmp);
	return (img);
}


void    load_graphics(t_mlx *mlx, t_cube *cube)
{
	mlx->graphics.no_txtr = textures_loader(mlx, cube->no_tex);
	mlx->graphics.so_txtr = textures_loader(mlx, cube->so_tex);
	mlx->graphics.ea_txtr = textures_loader(mlx, cube->ea_tex);
	mlx->graphics.we_txtr = textures_loader(mlx, cube->we_tex);
	mlx->graphics.loading_img = textures_loader(mlx, "textures/loading.png");
	mlx_resize_image(mlx->graphics.no_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.so_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.ea_txtr, W_HEIGHT, W_HEIGHT);
	mlx_resize_image(mlx->graphics.we_txtr, W_HEIGHT, W_HEIGHT);
}
