/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:22:28 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 13:31:16 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	set_fd(-1, cube->fd, 0);
}

void	init_cube(t_cube *cube)
{
	cube->no_tex = ft_strdup("");
	cube->so_tex = ft_strdup("");
	cube->we_tex = ft_strdup("");
	cube->ea_tex = ft_strdup("");
	cube->file_content = NULL;
	cube->map = NULL;
	cube->floor_color[0] = -1;
	cube->ceiling_color[0] = -1;
	cube->fd = 0;
}

void	set_fd(int fd1, int fd2, int flag)
{
	static int	first;
	static int	second;

	if (!flag && !first && fd1 != -1)
		first = fd1;
	if (!flag && !first && fd2 != -1)
		second = fd2;
	if (flag && first)
		close (first);
	if (flag && second)
		close (second);
}
