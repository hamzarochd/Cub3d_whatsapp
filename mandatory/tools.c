/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:59:41 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 09:25:52 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free (ptr);
	ptr = NULL;
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	i = 0;
	res = 0;
	if (str[i] == '\0')
		return (0);
	while (str [i] == '\n' || str [i] == '\t'
		|| str[i] == '\f' || str [i] == '\v' || str [i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str [i] >= '0' && str [i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (-1);
	return (res * sign);
}

void	decide(t_cube *cube, char **token, char *tag)
{
	if (!ft_strcmp(tag, "C"))
	{
		cube->ceiling_color[0] = ft_atoi(token[0]);
		cube->ceiling_color[1] = ft_atoi(token[1]);
		cube->ceiling_color[2] = ft_atoi(token[2]);
	}
	if (!ft_strcmp(tag, "F"))
	{
		cube->floor_color[0] = ft_atoi(token[0]);
		cube->floor_color[1] = ft_atoi(token[1]);
		cube->floor_color[2] = ft_atoi(token[2]);
	}
}

int	is_invalid_rgb(char *input, t_cube *cube, char *tag)
{
	int		count;
	char	**token;
	int		i;

	token = ft_split(input, ',');
	i = 0;
	count = 0;
	while (token[i])
		i++;
	if (i != 3)
		return (free_double(token), -1);
	i = 0;
	while (token[i])
	{
		count = ft_atoi(token[i]);
		if (count < 0 || count > 255)
		{
			free_double(token);
			return (-1);
		}
		decide(cube, token, tag);
		i++;
	}
	free_double(token);
	return (0);
}

void	free_all(t_cube *cube)
{
	int	i;

	free(cube->file_name);
	free(cube->no_tex);
	free(cube->so_tex);
	free(cube->we_tex);
	free(cube->ea_tex);
	i = 0;
	if (cube->map)
	{
		while (cube->map[i])
			free(cube->map[i++]);
	}
	free(cube->map);
	i = 0;
	if (cube->file_content)
	{
		while (cube->file_content[i])
			free(cube->file_content[i++]);
	}
	free(cube->file_content);
	if (cube->fd != 0)
		close(cube->fd);
}
