#include "cub3d.h"

int check_config(t_cube *cube)
{
    char    **splitted;
    char    *config;
    char    *line;
    int counter;
    
    counter = 0;
    while(cube->file_content[counter])
    {
        line = ft_strdup(cube->file_content[counter]);
        splitted =  ft_split(line, ' ');
        if (strcmp(splitted[0], "NO") == 0 && counter == 0)
        {
            if (cube->no_tex[0] != '\0')
                return (free(line), free_double(splitted),ft_printf("NO texture already set\n"), -1);
            free(cube->no_tex);
            cube->no_tex = strdup(line + ft_strlen(splitted[0]));
            cube->no_tex = ft_strtrim(cube->no_tex, " \t");
            counter++;
        }
        else if (strcmp(splitted[0], "SO") == 0 && counter == 1)
        {
            if (cube->so_tex[0] != '\0')
                return (free(line), free_double(splitted),ft_printf("SO texture already set\n"), -1);
            free(cube->so_tex);
            cube->so_tex = strdup(line + ft_strlen(splitted[0]));
            cube->so_tex = ft_strtrim(cube->so_tex, " \t");
            counter++;
        }
        else if (strcmp(splitted[0], "WE") == 0 && counter == 2)
        {
            if (cube->we_tex[0] != '\0')
                return (free(line), free_double(splitted),ft_printf("WE texture already set\n"), -1);
            free(cube->we_tex);
            cube->we_tex = strdup(line + ft_strlen(splitted[0]));
            cube->we_tex = ft_strtrim(cube->we_tex, " \t");
            counter++;
        }
        else if (strcmp(splitted[0], "EA") == 0 && counter == 3)
        {
            if (cube->ea_tex[0] != '\0')
                return (free(line), free_double(splitted),ft_printf("EA texture already set\n"), -1);
            free(cube->ea_tex);
            cube->ea_tex = strdup(line + ft_strlen(splitted[0]));
            cube->ea_tex = ft_strtrim(cube->ea_tex, " \t");
            counter++;
        }
        else if (strcmp(splitted[0], "F") == 0 && counter == 4)
        {
            if (cube->floor_color[0] != -1)
                return (ft_printf("floor color already set\n"), -1);
            if (is_invalid_rgb(line + ft_strlen(splitted[0]), cube, splitted[0]) == -1)
                return (free(line), free_double(splitted), printf("error1\n"), -1);
            counter++;
        }
        else if (strcmp(splitted[0], "C") == 0 && counter == 5)
        {
            if (cube->ceiling_color[0] != -1)
                return (ft_printf("ceiling color already set\n"), -1);
            if (is_invalid_rgb(line + ft_strlen(splitted[0]), cube, splitted[0]) == -1)
                return (free(line), free_double(splitted), printf("error1\n"), -1);
            counter++;
        }
        else
        {   
            if (counter != 6)
                return (free(line), free_double(splitted), printf("error\n"), -1);
            else
                return (free(line), free_double(splitted), counter);
        }
        free(line);
        free_double(splitted);
    }
    return (counter);
}

char    **refill_map(t_cube *cube)
{
    char **res;
    int i;
    int j;
    int z;
    int bigest_line;

    bigest_line = 0;
    i = 0;
    bigest_line = ft_strlen(cube->map[0]);
    while(cube->map[i])
    {
        if (ft_strlen(cube->map[i]) > bigest_line)
            bigest_line = ft_strlen(cube->map[i]);
        i++;
    }
    j = 0;
    res = calloc(i + 1, sizeof(char *));
    while (j < i)
    {
        z = 0;
        res[j] = calloc(bigest_line + 1, sizeof(char));
        while(cube->map[j][z])
        {
            res[j][z] = cube->map[j][z];
            z++;
        }
        while(z < bigest_line)
        {
            res[j][z] = ' ';
            z++;
        }
        res[j][z] = 0;
        j++;
    }
    res[j] = NULL;
    free_double(cube->map);
    return (res);
}

void init_cube(t_cube *cube)
{

    cube->no_tex = ft_strdup("");
    cube->so_tex = ft_strdup("");
    cube->we_tex = ft_strdup("");
    cube->ea_tex = ft_strdup("");
    cube->floor_color[0] = -1;
    cube->ceiling_color[0] = -1;
}

int check_map_name(char *str)
{
    int i;

    i = 0;
    if (!str)
        return(1);
    while(str[i] && str[i] != '.')
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

int read_file(t_cube *cube)
{
    int count;
    int i;
    char    *tmp;

    i = 0;
    count = 0;
    tmp = get_next_line(cube->fd); 
    while(tmp)
    {
        free(tmp);
        tmp = get_next_line(cube->fd);
        count++;
    }
    if (count == 0)
        return (ft_printf("map empty\n"), 1);
    cube->file_content = calloc(count + 1, sizeof(char *));
    close(cube->fd);
    cube->fd = open(cube->file_name, O_RDONLY);
    if (cube->fd == -1)
        return (ft_printf("fd error\n"), 1);
    tmp = get_next_line(cube->fd);
    while(tmp)
    {
        tmp = ft_strtrim_last(tmp, " \t\n\r");
        if (!tmp[0])
        {
            free(tmp);
            tmp = get_next_line(cube->fd);
            continue ;
        }
        cube->file_content[i] = ft_strdup(tmp);
        i++;
        free(tmp);
        tmp = get_next_line(cube->fd);
    }
    cube->file_content[i] = NULL;
    return (0);
}

int parse_file(t_cube *cube)
{
    int i;
    int j;

    i = check_config(cube);
    if (i == -1)
        return (free_double(cube->file_content),1);
    // while(cube->file_content[i])
    // {
    //     int w = check_config(cube, cube->file_content[i]);
    //     if (w == 1)
    //         return (1);
    //     else if (w == 2)
    //         break ;
    //     i++;
    // }
    j = i;
    while(cube->file_content[j])
        j++;
    cube->map = calloc(j - i + 1 , sizeof(char *));
    j = 0;
    while(cube->file_content[i])
    {
        cube->map[j] = strdup(cube->file_content[i]);
       i++;
       j++;
    }
    cube->map[j] = 0;

    free_double(cube->file_content);
    cube->map = refill_map(cube);
    return (0);
}

int check_map(t_cube *cube)
{
    int i = 0;
    int j;
    int player_count = 0;

    while (cube->map[i] != NULL) {
        j = 0;
        while (cube->map[i][j])
        {
            if (!strchr("NSWE01D ", cube->map[i][j]))
                return (ft_printf("Error: Invalid character '%c' at (%d, %d)\n", cube->map[i][j], i, j), 1);
            if (cube->map[i][j] == '0')
            {
                if (i == 0 || cube->map[i - 1][j] == ' ')
                    return (ft_printf("Error: '0' not closed on top at (%d, %d)\n", i, j), 1);
                if (cube->map[i + 1] == NULL || cube->map[i + 1][j] == ' ')
                    return (ft_printf("Error: '0' not closed on bottom at (%d, %d)\n", i, j), 1);
                if (j == 0 || cube->map[i][j - 1] == ' ') 
                    return (ft_printf("Error: '0' not closed on left at (%d, %d)\n", i, j), 1);
                if (cube->map[i][j + 1] == '\0' || cube->map[i][j + 1] == ' ') 
                    return (ft_printf("Error: '0' not closed on right at (%d, %d)\n", i, j), 1);
            }

            if (cube->map[i][j] == 'N' || cube->map[i][j] == 'S' || cube->map[i][j] == 'W' || cube->map[i][j] == 'E')
                player_count++;
            j++;
        }
        i++;
    }

    if (player_count != 1) {
        return (ft_printf("Error: There must be exactly one player on the map\n"), 1);
    }
    return (0);
}

void free_textures(t_cube *cube)
{
    free(cube->so_tex);
    free(cube->no_tex);
    free(cube->ea_tex);
    free(cube->we_tex);
}


int main_parsing(t_cube *cube, char **av)
{
  
    init_cube(cube);
    cube->file_name = ft_strdup(av[1]);
    if (check_map_name(cube->file_name) == 1)
    {
        ft_printf("map name error\n");
        free(cube->file_name);
        return (1);
    }
    cube->fd = open(cube->file_name, O_RDONLY);
    if (read_file(cube) == 1)
        return (free(cube->file_name) ,1);
    if (parse_file(cube) == 1)
        return (free(cube->file_name),free_textures(cube) ,1);
    if (check_map(cube) == 1)
        return (free(cube->file_name),1);
    printf("floor color %d, %d, %d\n", cube->floor_color[0], cube->floor_color[1], cube->floor_color[2]);
    printf("ceiling color %d, %d, %d\n", cube->ceiling_color[0], cube->ceiling_color[1], cube->ceiling_color[2]);

    return (0);
}
