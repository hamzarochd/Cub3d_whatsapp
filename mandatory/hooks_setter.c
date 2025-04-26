#include "cub3d.h"


void set_hooks(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx_cnx, keydown_handler, mlx);
	mlx_loop_hook(mlx->mlx_cnx, render, mlx);
}