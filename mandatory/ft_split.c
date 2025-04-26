#include "cub3d.h"

static int	check_words(const char *str, char c)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (str[j])
	{
		if (str[j] != c && check == 0)
		{
			check = 1;
			i++;
		}
		else if (str[j] == c)
			check = 0;
		j++;
	}
	return (i);
}

static char	*alloc_word(const char *s, int d, int e)
{
	int		i;
	char	*word;

	word = (char *)salloc ((e - d) + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (d < e)
	{
		word[i] = s[d];
		d++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**alloc_split(const char *s, char c)
{
	char	**split;

	split = (char **)salloc ((check_words(s, c) + 1) * sizeof (char *));
	if (split == NULL)
		return (NULL);
	return (split);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		e;
	int		len;
	char	**split;

	len = 0;
	while (s[len] != '\0')
		len++;
	split = alloc_split(s, c);
	e = -1;
	i = 0;
	j = 0;
	while (i <= len)
	{
		if (s[i] != c && e == -1)
			e = i;
		else if ((s[i] == c || i == len) && e >= 0)
		{
			split[j++] = alloc_word(s, e, i);
			e = -1;
		}
		i++;
	}
	return (split[j] = NULL, split);
}
