/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouigui <ymouigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:58:44 by ymouigui          #+#    #+#             */
/*   Updated: 2025/04/27 11:58:44 by ymouigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_char(char const *set, char c)
{
	int	w;

	w = 0;
	while (set[w] != '\0')
	{
		if (set[w] == c)
			return (1);
		w++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	int		i;
	int		j;
	int		l;
	int		len;
	char	*ptr;

	len = 0;
	while (s1[len] != '\0')
		len++;
	i = 0;
	while (s1[i] && check_char(set, s1[i]) == 1)
		i++;
	l = len;
	while (i < l && check_char(set, s1[l - 1]) == 1)
		l--;
	ptr = (char *)safe_malloc(l - i + 1);
	if (ptr == NULL)
		return (NULL);
	j = 0;
	while (i < l)
		ptr[j++] = s1[i++];
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strtrim_last(char *s1, char const *set)
{
	int		i;
	int		j;
	int		l;
	char	*ptr;

	l = 0;
	while (s1[l] != '\0')
		l++;
	while (l > 0 && check_char(set, s1[l - 1]) == 1)
		l--;
	ptr = (char *)safe_malloc(l + 1);
	if (ptr == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (i < l)
		ptr[j++] = s1[i++];
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	lenofs;
	char	*s2;

	i = 0;
	lenofs = ft_strlen(s1)+1;
	if (!s1)
		return (NULL);
	s2 = safe_malloc(lenofs * sizeof(char));
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
