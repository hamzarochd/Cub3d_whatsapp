/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:58:28 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/27 14:37:19 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_cube	cube;

	mlx.time = mlx_get_time();
	if (ac != 2)
	{
		printf("Error\nneed file name !\n");
		return (1);
	}
	if (main_parsing(&cube, av))
		return (1);
	ft_bzero(&mlx, sizeof(t_mlx));
	initializer(&mlx, &cube);
	load_graphics(&mlx, &cube);
	put_images(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_cnx);
}
