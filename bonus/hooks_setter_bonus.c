#include "cub3d_bonus.h"


void    mouse_handler(double xpos, double ypos, void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	const double center_x = W_WIDTH/2;
	double delta_x = xpos - center_x;

	if (ypos)
		ypos = 1;
	if (mlx->is_loading)
		return ;
	mlx->player.rot_angle -= (PI/2) * (delta_x/center_x);
	if (mlx->player.rot_angle >= 2*PI)
		mlx->player.rot_angle -= 2*PI;
	if (mlx->player.rot_angle < 0)
		mlx->player.rot_angle += 2*PI;

	mlx_set_mouse_pos(mlx->mlx_cnx, W_WIDTH/2, W_HEIGHT/2);
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