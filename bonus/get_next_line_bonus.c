/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:34:26 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/29 11:41:53 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	end_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_line(char **str)
{
	char	*s1;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!*str)
		return (NULL);
	if (*(str)[i] == '\0')
		return (NULL);
	i = end_line(*str);
	s1 = (char *)safe_malloc((ft_strlen(*str) - i + 1));
	if (!s1)
		return (NULL);
	while ((*str)[i])
		s1[j++] = (*str)[i++];
	s1[j] = '\0';
	if (!s1[0])
		return (NULL);
	*str = NULL;
	return (s1);
}

char	*ft_read(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (NULL);
	i = end_line(str);
	line = (char *)safe_malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*s;
	ssize_t		n;

	n = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	s = safe_malloc((size_t)BUFFER_SIZE + 1);
	if (!s)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')) && n != 0)
	{
		n = read(fd, s, BUFFER_SIZE);
		if (n == -1)
			return (NULL);
		s[n] = '\0';
		buffer = ft_strjoin(buffer, s);
	}
	s = ft_read(buffer);
	if (!s)
		return (NULL);
	buffer = ft_line(&buffer);
	return (s);
}
