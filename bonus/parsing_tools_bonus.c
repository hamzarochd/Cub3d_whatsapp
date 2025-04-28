/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:22:28 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/28 12:35:31 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_textures(t_cube *cube)
{
	free(cube->so_tex);
	free(cube->no_tex);
	free(cube->ea_tex);
	free(cube->we_tex);
}

int	check_map_name(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		if (i == 0)
			return (1);
		i++;
		if (ft_strcmp(str + i, "cub") == 0)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

void	handle_fd(t_cube *cube)
{
	close(cube->fd);
	cube->fd = open(cube->file_name, O_RDONLY);
}
