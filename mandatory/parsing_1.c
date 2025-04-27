/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:19 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 14:34:23 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_config(t_cube *cube, char **splitted, char *line,
	int counter)
{
	int	ret;

	ret = check_texture(cube, splitted, line);
	if (ret == 1)
		counter++;
	else if (ret == -1)
		return (printf("Error\nerror in config\n"), -1);
	else
	{
		ret = check_color(cube, splitted, line);
		if (ret == 1)
			counter++;
		else if (ret == -1)
			return (printf("Error\nerror in config\n"), -1);
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
	free_double(cube->map);
	return (res);
}

void	init_cube(t_cube *cube)
{
	cube->no_tex = ft_strdup("");
	cube->so_tex = ft_strdup("");
	cube->we_tex = ft_strdup("");
	cube->ea_tex = ft_strdup("");
	cube->floor_color[0] = -1;
	cube->ceiling_color[0] = -1;
}
