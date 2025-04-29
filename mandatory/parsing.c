/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:27 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 10:30:55 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file(t_cube *cube)
{
	int	i;
	int	j;

	i = check_config(cube);
	if (i == -1)
		return (1);
	if (i != 6)
		return (printf("Error\ncongif err\n"), 1);
	j = i;
	while (cube->file_content[j])
		j++;
	cube->map = ft_calloc(j - i + 1, sizeof(char *));
	j = 0;
	while (cube->file_content[i])
	{
		cube->map[j] = ft_strdup(cube->file_content[i]);
		i++;
		j++;
	}
	cube->map[j] = 0;
	cube->map = refill_map(cube);
	return (0);
}

static int	check_map_char(char c, int i, int j, t_cube *cube)
{
	if (!ft_strchr("NSWE01 ", c))
		return (printf("Error\nInvalid character '%c' at (%d, %d)\n",
				c, i, j), 1);
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (i == 0 || cube->map[i - 1][j] == ' ')
			return (printf("Error\n'%c' not closed on top at (%d, %d)\n",
					c, i, j), 1);
		if (cube->map[i + 1] == NULL || cube->map[i + 1][j] == ' ')
			return (printf("Error\n'%c' not closed on bottom at (%d, %d)\n",
					c, i, j), 1);
		if (j == 0 || cube->map[i][j - 1] == ' ')
			return (printf("Error\n'%c' not closed on left at (%d, %d)\n",
					c, i, j), 1);
		if (cube->map[i][j + 1] == '\0' || cube->map[i][j + 1] == ' ')
			return (printf("Error\n'%c' not closed on right at (%d, %d)\n",
					c, i, j), 1);
	}
	return (0);
}

static int	check_player(char c, int *player_count)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		(*player_count)++;
	return (0);
}

int	check_map(t_cube *cube)
{
	int	i;
	int	j;
	int	player_count;

	i = -1;
	player_count = 0;
	while (cube->map[++i] != NULL)
	{
		j = 0;
		while (cube->map[i][j])
		{
			if (check_map_char(cube->map[i][j], i, j, cube) == 1)
				return (1);
			check_player(cube->map[i][j], &player_count);
			j++;
		}
	}
	if (player_count != 1)
		return (printf("Error\nError: There must be exactly one player\n"), 1);
	return (0);
}

int	main_parsing(t_cube *cube, char **av)
{
	init_cube(cube);
	cube->file_name = ft_strdup(av[1]);
	if (check_map_name(cube->file_name) == 1)
	{
		printf("Error\nmap name error\n");
		return (1);
	}
	cube->fd = open(cube->file_name, O_RDONLY);
	if (cube->fd == -1)
		return (printf("Error\nfd error\n"), 1);
	if (read_file(cube) == 1)
		return ( 1);
	if (parse_file(cube) == 1)
		return ( 1);
	if (check_map(cube) == 1)
		return ( 1);
	close (cube->fd);
	return (0);
}
