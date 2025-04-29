/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:24 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/28 15:06:11 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_type(char *dir)
{
	if (ft_strcmp(dir, "NO") == 0)
		return (0);
	else if (ft_strcmp(dir, "SO") == 0)
		return (1);
	else if (ft_strcmp(dir, "WE") == 0)
		return (2);
	else if (ft_strcmp(dir, "EA") == 0)
		return (3);
	return (-1);
}

static int	process_texture(char **tex, char *line, char *dir)
{
	if ((*tex)[0] != '\0')
		return (printf("Error\n%s texture already set\n", dir), -1);
	free(*tex);
	*tex = ft_strdup(line + ft_strlen(dir));
	*tex = ft_strtrim(*tex, " \t");
	return (0);
}

int	check_texture(t_cube *cube, char **splitted, char *line)
{
	char	*dir;
	int		type;

	dir = splitted[0];
	type = check_texture_type(dir);
	if (type == -1)
		return (0);
	if (type == 0 && process_texture(&cube->no_tex, line, dir) == -1)
		return (-1);
	else if (type == 1 && process_texture(&cube->so_tex, line, dir) == -1)
		return (-1);
	else if (type == 2 && process_texture(&cube->we_tex, line, dir) == -1)
		return (-1);
	else if (type == 3 && process_texture(&cube->ea_tex, line, dir) == -1)
		return (-1);
	return (1);
}

int	check_color(t_cube *cube, char **splitted, char *line)
{
	if (ft_strcmp(splitted[0], "F") == 0)
	{
		if (cube->floor_color[0] != -1)
			return (printf("Error\nfloor color already set\n"), -1);
		if (is_invalid_rgb(line + ft_strlen(splitted[0]), cube, splitted[0])
			== -1)
		{
			return (printf("Error\ncolor\n"), -1);
		}
		return (1);
	}
	else if (ft_strcmp(splitted[0], "C") == 0)
	{
		if (cube->ceiling_color[0] != -1)
			return (printf("Error\nceiling color already set\n"), -1);
		if (is_invalid_rgb(line + ft_strlen(splitted[0]), cube, splitted[0])
			== -1)
		{
			return (printf("Error\ncolor\n"), -1);
		}
		return (1);
	}
	return (0);
}

int	check_config(t_cube *cube)
{
	char	**splitted;
	char	*line;
	int		counter;
	int		i;
	int		x;

	i = 0;
	counter = 0;
	while (cube->file_content[i] && counter != 6)
	{
		cube->file_content[i] = ft_strtrim(cube->file_content[i], " \t");
		x = -1;
		while (cube->file_content[i][++x])
			if (cube->file_content[i][x] == '\t')
				cube->file_content[i][x] = ' ';
		line = ft_strdup(cube->file_content[i]);
		splitted = ft_split(line, ' ');
		counter = handle_config(cube, splitted, line, counter);
		if (counter == -1)
			return (free_double(splitted), free_textures(cube), free(line), -1);
		free(line);
		free_double(splitted);
		i++;
	}
	return (counter);
}
