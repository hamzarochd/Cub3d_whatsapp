#include "cub3d_bonus.h"



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
	load_graphics(&mlx, &cube);
	put_images(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_cnx);
}
