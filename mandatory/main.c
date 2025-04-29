/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:15 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 13:05:04 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (safe_malloc(-1), 1);
	ft_bzero(&mlx, sizeof(t_mlx));
	initializer(&mlx, &cube);
	load_graphics(&mlx, &cube);
	put_images(&mlx);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_cnx);
}
