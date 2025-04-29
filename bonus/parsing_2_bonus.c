/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:22 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 11:40:24 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	count_lines(t_cube *cube)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = get_next_line(cube->fd);
	while (tmp)
	{
		tmp = get_next_line(cube->fd);
		count++;
	}
	if (count == 0)
		return (printf("Error\nmap empty\n"), -1);
	return (count);
}

int	first_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else if (str[i] == '1' || str[i] == '0' || str[i] == 'D')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	check_tmp(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (first_char(file[i++]))
			break ;
	}
	while (file[i])
	{
		file[i] = ft_strtrim(file[i], " \t");
		if (file[i] && (file[i][0] == '\n' || !file[i][0] || file[i][0] == 13))
		{
			printf("Error\nnew line inside map\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	read_lines(t_cube *cube, char **tmp_d)
{
	int		i;
	int		d;
	char	*tmp;

	i = 0;
	d = 0;
	tmp = get_next_line(cube->fd);
	while (tmp)
	{
		tmp_d[d++] = ft_strdup(tmp);
		tmp = ft_strtrim_last(tmp, " \t\n\r");
		if (!tmp[0])
		{
			tmp = get_next_line(cube->fd);
			continue ;
		}
		cube->file_content[i++] = ft_strdup(tmp);
		tmp = get_next_line(cube->fd);
	}
	cube->file_content[i] = NULL;
	tmp_d[d] = NULL;
	return (0);
}

int	read_file(t_cube *cube)
{
	int		count;
	char	**tmp_d;

	count = count_lines(cube);
	if (count == -1)
		return (1);
	cube->file_content = ft_calloc(count + 1, sizeof(char *));
	tmp_d = ft_calloc(count + 1, sizeof(char *));
	handle_fd(cube);
	read_lines(cube, tmp_d);
	if (check_tmp(tmp_d) == 1)
		return (1);
	return (0);
}
