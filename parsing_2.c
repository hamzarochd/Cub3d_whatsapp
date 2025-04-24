#include "cub3d.h"

int	check_map_name(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		if (i == 0)
			return (1);
		i++;
		if (strcmp(str + i, "cub") == 0)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

static int	count_lines(t_cube *cube)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = get_next_line(cube->fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(cube->fd);
		count++;
	}
	if (count == 0)
		return (ft_printf("map empty\n"), -1);
	return (count);
}

static void	handle_fd(t_cube *cube)
{
	close(cube->fd);
	cube->fd = open(cube->file_name, O_RDONLY);
}

int	read_file(t_cube *cube)
{
	int		i;
	char	*tmp;
	int		count;

	count = count_lines(cube);
	if (count == -1)
		return (free_textures(cube), 1);
	cube->file_content = calloc(count + 1, sizeof(char *));
	handle_fd(cube);
	i = 0;
	tmp = get_next_line(cube->fd);
	while (tmp)
	{
		tmp = ft_strtrim_last(tmp, " \t\n\r");
		if (!tmp[0])
		{
			free(tmp);
			tmp = get_next_line(cube->fd);
			continue ;
		}
		cube->file_content[i++] = ft_strdup(tmp);
		free(tmp);
		tmp = get_next_line(cube->fd);
	}
	return (cube->file_content[i] = NULL, 0);
}

void	free_textures(t_cube *cube)
{
	free(cube->so_tex);
	free(cube->no_tex);
	free(cube->ea_tex);
	free(cube->we_tex);
}
