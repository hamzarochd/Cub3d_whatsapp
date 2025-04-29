/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:30:09 by hrochd            #+#    #+#             */
/*   Updated: 2025/04/29 11:41:05 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		return (-1);
	i = 0;
	while (token[i])
	{
		count = ft_atoi(token[i]);
		if (count < 0 || count > 255)
			return (-1);
		decide(cube, token, tag);
		i++;
	}
	return (0);
}
