/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:34:26 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/26 16:29:48 by hrochd           ###   ########.fr       */
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
		return (free(*str), *str = NULL, NULL);
	i = end_line(*str);
	s1 = (char *)salloc((ft_strlen(*str) - i + 1));
	if (!s1)
		return (my_free(s1, str), NULL);
	while ((*str)[i])
		s1[j++] = (*str)[i++];
	s1[j] = '\0';
	if (!s1[0])
		return (my_free(s1, str), NULL);
	free(*str);
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
	line = (char *)salloc(sizeof(char) * i + 1);
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

char	*my_free(char *s1, char **s2)
{
	free(s1);
	free(*s2);
	*s2 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*s;
	ssize_t		n;

	n = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	s = salloc((size_t)BUFFER_SIZE + 1);
	if (!s)
		return (free(buffer), buffer = NULL, NULL);
	while (!(ft_strchr(buffer, '\n')) && n != 0)
	{
		n = read(fd, s, BUFFER_SIZE);
		if (n == -1)
			return (my_free(s, &buffer), NULL);
		s[n] = '\0';
		buffer = ft_strjoin(buffer, s);
	}
	free(s);
	s = ft_read(buffer);
	if (!s)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_line(&buffer);
	return (s);
}
