/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:19 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 11:33:09 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_config_type(char *dir)
{
	if (ft_strcmp(dir, "NO") == 0)
		return (0);
	else if (ft_strcmp(dir, "SO") == 0)
		return (1);
	else if (ft_strcmp(dir, "WE") == 0)
		return (2);
	else if (ft_strcmp(dir, "EA") == 0)
		return (3);
	else if (ft_strcmp(dir, "C") == 0)
		return (9);
	else if (ft_strcmp(dir, "F") == 0)
		return (8);
	return (printf("Error\ninvalid config"), -1);
}

int	handle_config(t_cube *cube, char **splitted, char *line,
	int counter)
{
	int	ret;

	if (check_config_type(splitted[0]) == -1)
		return (-1);
	ret = check_texture(cube, splitted, line);
	if (ret == 1)
		counter++;
	else if (ret == -1)
		return (-1);
	else
	{
		ret = check_color(cube, splitted, line);
		if (ret == 1)
			counter++;
		else if (ret == -1)
			return (-1);
	}
	return (counter);
}

static int	get_bigest_line(t_cube *cube)
{
	int	i;
	int	bigest_line;

	i = 0;
	bigest_line = ft_strlen(cube->map[0]);
	while (cube->map[i])
	{
		if (ft_strlen(cube->map[i]) > bigest_line)
			bigest_line = ft_strlen(cube->map[i]);
		i++;
	}
	return (bigest_line);
}

static char	*fill_line(char *map_line, int bigest_line)
{
	char	*res;
	int		z;

	z = 0;
	res = ft_calloc(bigest_line + 1, sizeof(char));
	while (map_line[z])
	{
		res[z] = map_line[z];
		z++;
	}
	while (z < bigest_line)
	{
		res[z] = ' ';
		z++;
	}
	res[z] = 0;
	return (res);
}

char	**refill_map(t_cube *cube)
{
	char	**res;
	int		i;
	int		j;
	int		bigest_line;

	bigest_line = get_bigest_line(cube);
	i = 0;
	while (cube->map[i])
		i++;
	j = 0;
	res = ft_calloc(i + 1, sizeof(char *));
	while (j < i)
	{
		res[j] = fill_line(cube->map[j], bigest_line);
		j++;
	}
	res[j] = NULL;
	return (res);
}
