#include "cub3d.h"

uint32_t    rgb(int r, int g, int b, int a)
{
    return (((r & 0xFF) << 24) | ((g & 0xFF) << 16)
        | ((b & 0xFF) << 8) | (a & 0xFF));
}

int check_map_name(char *str)
{
    int i;

    i = 0;
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
    while(get_next_line(cube->fd))
        count++;
    if (count == 0)
        return (printf("map empty\n"), 1);
    cube->file_content = calloc(count + 1, sizeof(char *));
    close(cube->fd);
    cube->fd = open(cube->file_name, O_RDONLY);
    if (cube->fd == -1)
        return (printf("fd error\n"), 1);
    tmp = get_next_line(cube->fd);
    while(tmp)
    {
        tmp = ft_strtrim(tmp, " \t\n\r");
        if (!tmp[0])
        {
            tmp = get_next_line(cube->fd);
            continue ;
        }
        cube->file_content[i] = ft_strdup(tmp);
        i++;
        tmp = get_next_line(cube->fd);
    }
    cube->file_content[i] = NULL;
    return (0);
}

int check_if_done(t_cube *cube)
{
    if (cube->no_tex == NULL)
            return (1);

    if (cube->so_tex == NULL)
            return (1);
    if (cube->we_tex == NULL)
            return (1);
    if (cube->ea_tex == NULL)
            return (1);
    if (cube->floor_color == NULL)
            return (1);
    if (cube->ceiling_color == NULL)
            return (1);
    return (0);
}

char    *color_join(char    **splitted)
{
    char    *res;
    int i;

    i = 2;
    if (splitted[1])
        res = ft_strdup(splitted[1]);
    else
        return (NULL);
    while (splitted[i])
    {
        res = ft_strjoin(res, splitted[i]);
        i++; 
    }
    return (res);
}


int check_config(t_cube *cube, char *line)
{
    char    **splitted;
    static int counter;
    
    if (!line)
        return 0;

    splitted = ft_split(line, ' ');
    if (strcmp(splitted[0], "NO") == 0)
    {
        if (cube->no_tex != NULL)
            return (printf("NO texture already set\n"), 1);
        cube->no_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "SO") == 0)
    {
        if (cube->so_tex != NULL)
            return (printf("SO texture already set\n"), 1);
        cube->so_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "WE") == 0)
    {
        if (cube->we_tex != NULL)
            return (printf("WE texture already set\n"), 1);
        cube->we_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "EA") == 0)
    {
        if (cube->ea_tex != NULL)
            return (printf("EA texture already set\n"), 1);
        cube->ea_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "F") == 0)
    {
        if (cube->floor_color != NULL)
            return (printf("floor color already set\n"), 1);
        cube->floor_color = color_join(splitted);
        counter++;
    }
    else if (strcmp(splitted[0], "C") == 0)
    {
        if (cube->ceiling_color != NULL)
            return (printf("ceiling color already set\n"), 1);
        cube->ceiling_color = color_join(splitted);
        counter++;
    }
    else
    {   
        if (counter != 6)
           return (printf("error\n"), 1);
        else
            return (2);
    }
    return (0);
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
    return (res);
}

int parse_file(t_cube *cube)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(cube->file_content[i])
    {
        int w = check_config(cube, cube->file_content[i]);
        if (w == 1)
            return (1);
        else if (w == 2)
            break ;
        i++;
    }
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
            if (strchr("NSWE01 ", cube->map[i][j]) == NULL)
                return (printf("Error: Invalid character '%c' at (%d, %d)\n", cube->map[i][j], i, j), 1);
            if (cube->map[i][j] == '0')
            {
                if (i == 0 || cube->map[i - 1][j] == ' ')
                    return (printf("Error: '0' not closed on top at (%d, %d)\n", i, j), 1);
                if (cube->map[i + 1] == NULL || cube->map[i + 1][j] == ' ')
                    return (printf("Error: '0' not closed on bottom at (%d, %d)\n", i, j), 1);
                if (j == 0 || cube->map[i][j - 1] == ' ') 
                    return (printf("Error: '0' not closed on left at (%d, %d)\n", i, j), 1);
                if (cube->map[i][j + 1] == '\0' || cube->map[i][j + 1] == ' ') 
                    return (printf("Error: '0' not closed on right at (%d, %d)\n", i, j), 1);
            }

            if (cube->map[i][j] == 'N' || cube->map[i][j] == 'S' || cube->map[i][j] == 'W' || cube->map[i][j] == 'E')
                player_count++;
            j++;
        }
        i++;
    }

    if (player_count != 1) {
        return (printf("Error: There must be exactly one player on the map\n"), 1);
    }
    return (0);
}


void init_cube(t_cube *cube)
{

    cube->no_tex = NULL;
    cube->so_tex = NULL;
    cube->we_tex = NULL;
    cube->ea_tex = NULL;
    cube->floor_color = NULL;
    cube->ceiling_color = NULL;
}


void	my_mlx_put_pixel(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
    // printf("Adrees : is %d\t%d\n",(x) , y);
	*(unsigned int *)(img->addr + offset) = color;
}

int draw_line(t_mlx *mlx, t_point start, t_point end)
{
    double  delta_x;
    double  delta_y;
    int     pixels;
    t_point pixel_pt;

    if(end.x == -1 || end.y == -1)
        return (1);

    delta_x = end.x - start.x;
    delta_y = end.y - start.y;
    pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));

    delta_x /= pixels;
    delta_y /= pixels;
    
    pixel_pt = start;
    // printf("(%f ,%f) --> (%f, %f)\n", start.x, start.y, end.x, end.y);
    // printf("drawn line from (%f, %f) to ", pixel_pt.x, pixel_pt.y);
    while (pixels)
    {
        mlx_put_pixel(mlx->img, pixel_pt.x, pixel_pt.y, rgb(255, 255, 255, 255));
        pixel_pt.x += delta_x;
        pixel_pt.y += delta_y;
        pixels--;
    }
    // printf("(%f, %f)\n", pixel_pt.x, pixel_pt.y);
    return 0;
}

void draw_filled_circle(t_mlx *mlx, int x_center, int y_center, int radius, int color)
{
    int x, y;

    for (y = y_center - radius; y <= y_center + radius; y++)
    {
        for (x = x_center - radius; x <= x_center + radius; x++)
        {
            // Check if the point is within the circle using the equation: (x - xc)^2 + (y - yc)^2 <= r^2
            if ((x - x_center) * (x - x_center) + (y - y_center) * (y - y_center) <= radius * radius)
            {
                mlx_put_pixel(mlx->img, x, y, color);
            }
        }
    }
}

int check_diagonal(char **map, int xtile, int ytile, t_mlx *mlx)
{
    // int target_x;
    // int target_y;
    int player_x;
    int player_y;

    player_x = mlx->player->x_player/TILE_SIZE;
    player_y = mlx->player->y_player/TILE_SIZE;
    // target_x = player_x + (xtile - player_x);
    // target_y = player_y + (ytile - player_y);

    if (map[player_y][xtile] == '1' && map[ytile][player_x] == '1')
        return 1;
    return 0;
}

int is_in_wall(char **map, double x, double y, t_mlx *mlx)
{
    int map_x;
    int map_y;

    map_x = x / TILE_SIZE;
    map_y = y / TILE_SIZE;

    // printf("mapx = %d\nmapy = %d\n", );
    if (map_x < (mlx->map->width / TILE_SIZE) && map_y < (mlx->map->height / TILE_SIZE)
        && map_x >= 0 && map_y >= 0)
    {
        if(map[map_y][map_x] == '1')
            return 1;
        else
        {
            // printf("old x : %d\t\t\told y : %d\nnew x : %d\t\t\tnew y : %d\n", (int)(mlx->player->x_player/TILE_SIZE), (int)(mlx->player->y_player/TILE_SIZE), map_x, map_y);
            // if (map_x != (mlx->player->x_player/TILE_SIZE) && map_y != (mlx->player->y_player/TILE_SIZE))
            //     return (check_diagonal(map, map_x, map_y, mlx));
            return 0;
        }
    }
    return 1;
}

t_point get_h_wall_v(t_mlx *mlx, char **map, t_point player_pt, double ray_angle, double  *ray_lenght)
{
    t_point wall_pt;
    double  angle;
    double  next_wall_y;
    double  found_wall;
    double  ht;
    int     quarter;
    t_point unit_vec;

    wall_pt.x = 0;
    wall_pt.y = 0;
    unit_vec.x = 0;
    unit_vec.y = 0;
    angle = 0;
    next_wall_y = 0;
    found_wall = 0;
    ht = 0;
    quarter = 0;

    // if (ray_angle <= PI)
    //     angle = ray_angle;
    // else if (ray_angle > PI)
    //     angle = (2*PI) - ray_angle;

    if (ray_angle == PI || ray_angle == 0)
    {
        unit_vec.y = INT_MAX;
        unit_vec.x = INT_MAX;
        *ray_lenght = INT_MAX;
        return unit_vec;
    }
    unit_vec.x = cos(ray_angle);
    unit_vec.y = sin(ray_angle);


    if (unit_vec.y > 0)
        wall_pt.y = TILE_SIZE * (int)(player_pt.y / TILE_SIZE);
    else
        wall_pt.y = (TILE_SIZE * ((int)(player_pt.y / TILE_SIZE) + 1));

    double scaling_factor = 0;

    scaling_factor = (player_pt.y - wall_pt.y) / unit_vec.y;
    
    wall_pt.x = player_pt.x + (scaling_factor * unit_vec.x);


    while (!found_wall)
    {
        if ((unit_vec.y > 0 && is_in_wall(map, wall_pt.x, wall_pt.y - 1, mlx)) ||
            (unit_vec.y < 0 && is_in_wall(map, wall_pt.x, wall_pt.y + 1, mlx)))
        {
            found_wall = 1;
            break;
        }

        if (unit_vec.y > 0)
            wall_pt.y -= TILE_SIZE;
        else
            wall_pt.y += TILE_SIZE;

        scaling_factor = (player_pt.y - wall_pt.y) / unit_vec.y;

        wall_pt.x = player_pt.x + (scaling_factor * unit_vec.x); 
        
    }
    
    *ray_lenght = sqrt(((wall_pt.x - player_pt.x) * (wall_pt.x - player_pt.x)) + ((wall_pt.y - player_pt.y) * (wall_pt.y - player_pt.y)));
    return (wall_pt);
}

t_point get_v_wall_v(t_mlx *mlx, char **map, t_point player_pt, double ray_angle, double  *ray_lenght)
{
    t_point wall_pt;
    double  found_wall;
    t_point unit_vec;

    wall_pt.x = 0;
    wall_pt.y = 0;
    unit_vec.x = 0;
    unit_vec.y = 0;
    found_wall = 0;

    if (ray_angle == PI/ 2 || ray_angle == 3*(PI / 2))
    {
        unit_vec.y = INT_MAX;
        unit_vec.x = INT_MAX;
        *ray_lenght = INT_MAX;
        return unit_vec;
    }
    unit_vec.x = cos(ray_angle);
    unit_vec.y = sin(ray_angle);


    if (unit_vec.x < 0)
        wall_pt.x = TILE_SIZE * (int)(player_pt.x / TILE_SIZE);
    else
        wall_pt.x = (TILE_SIZE * ((int)(player_pt.x / TILE_SIZE) + 1));

    double scaling_factor = 0;

    scaling_factor = (player_pt.x - wall_pt.x) / unit_vec.x;
    
    wall_pt.y = player_pt.y + (scaling_factor * unit_vec.y);


    while (!found_wall)
    {
        if ((unit_vec.x > 0 && is_in_wall(map, wall_pt.x + 1, wall_pt.y, mlx)) ||
            (unit_vec.x < 0 && is_in_wall(map, wall_pt.x - 1, wall_pt.y, mlx)))
        {
            found_wall = 1;
            break;
        }

        if (unit_vec.x > 0)
            wall_pt.x += TILE_SIZE;
        else
            wall_pt.x -= TILE_SIZE;

        scaling_factor = (player_pt.x - wall_pt.x) / unit_vec.x;

        wall_pt.y = player_pt.y + (scaling_factor * unit_vec.y); 
        
    }
    
    *ray_lenght = sqrt(((wall_pt.x - player_pt.x) * (wall_pt.x - player_pt.x)) + ((wall_pt.y - player_pt.y) * (wall_pt.y - player_pt.y)));
    return (wall_pt);
}

t_point get_h_wall(t_mlx *mlx, char **map, t_point player_pt, double ray_angle, double  *ray_lenght)
{
    t_point wall_pt;
    double  angle;
    double  cat;
    double  found_wall;
    double  ht;

    wall_pt.x = 0;
    wall_pt.y = 0;
    angle = 0;
    cat = 0;
    found_wall = 0;
    ht = 0;

    if (ray_angle < PI / 2)
        angle = ray_angle;
    else if (ray_angle < PI)
        angle = PI - ray_angle;
    else if (ray_angle < ((3 * PI) / 2))
        angle = ray_angle - PI;
    else
        angle = (2 * PI) - ray_angle;
    // angle = ray_angle;
    
    // printf("ray_angle = %f radians --> %f degrees\nangle = %f radians --> %f degrees\n", ray_angle, (ray_angle * 180) / PI, angle, (angle * 180) / PI);

    if (ray_angle < PI)
        cat = player_pt.y - (TILE_SIZE * (int)(player_pt.y / TILE_SIZE));
    else
        cat = (TILE_SIZE * ((int)(player_pt.y / TILE_SIZE) + 1)) - player_pt.y;

    // printf("y = %f\ncat = %f\n", player_pt.y, cat);



    while (!found_wall)
    {
        if (ray_angle == PI/2 || ray_angle == (3*PI)/2)
            ht = cat;
        else if (ray_angle == PI || ray_angle == 0)
        {
            wall_pt.x = INT_MAX;
            wall_pt.y = INT_MAX;
            *ray_lenght = INT_MAX;
            return (wall_pt);
        }
        else
            ht = cat / sin(angle);

        *ray_lenght += ht;

        // printf("ht = %f\n", ht);
        if (ray_angle <= PI/2)
        {
            wall_pt.y = player_pt.y - cat;
            wall_pt.x = player_pt.x + sqrt((ht * ht) - (cat * cat));
            // printf("Q1\n");
        }
        else if (ray_angle < PI && ray_angle > PI/2)
        {
            wall_pt.y = player_pt.y - cat;
            wall_pt.x = player_pt.x - sqrt((ht * ht) - (cat * cat));
            // printf("Q2\n");
        }
        else if (ray_angle > PI && ray_angle <= (3*PI)/2)
        {
            wall_pt.y = player_pt.y + cat;
            wall_pt.x = player_pt.x - sqrt((ht * ht) - (cat * cat));
            // printf("Q3\n");
        }
        else if (ray_angle > (3*PI)/2)
        {
            wall_pt.y = player_pt.y + cat;
            wall_pt.x = player_pt.x + sqrt((ht * ht) - (cat * cat));
            // printf("Q4\n");
        }

        if(wall_pt.x > mlx->map->width || wall_pt.x < 0)
        {
            wall_pt.x = INT_MAX;
            wall_pt.y = INT_MAX;
            *ray_lenght = INT_MAX;
            return (wall_pt);
        }
        
        if ((ray_angle < PI && is_in_wall(map, wall_pt.x, wall_pt.y - 1, mlx)) ||
            (ray_angle > PI && is_in_wall(map, wall_pt.x, wall_pt.y + 1, mlx)))
        {
            found_wall = 1;
        }
        else
        {
            cat = TILE_SIZE;
            player_pt = wall_pt;
        }
        
        // printf("horizontal_intersection -> (%f, %f)\n", wall_pt.x, wall_pt.y);
    }
    

    // printf("is in wall = %d\n", is_in_wall(map, TILE_SIZE * 2.5, TILE_SIZE - 1, mlx));
    

    return wall_pt;
}

t_point get_v_wall(t_mlx *mlx, char **map, t_point player_pt, double ray_angle, double  *ray_lenght)
{
    t_point wall_pt;
    double  angle;
    double  cat;
    double  found_wall;
    double  ht;

    wall_pt.x = 0;
    wall_pt.y = 0;
    angle = 0;
    cat = 0;
    found_wall = 0;
    ht = 0;

    if (ray_angle < PI / 2)
        angle = ray_angle;
    else if (ray_angle <= PI)
        angle = PI - ray_angle;
    else if (ray_angle < ((3 * PI) / 2))
        angle = ray_angle - PI;
    else
        angle = (2 * PI) - ray_angle;
    // angle = ray_angle;
    
    // printf("ray_angle = %f radians --> %f degrees\nangle = %f radians --> %f degrees\n", ray_angle, (ray_angle * 180) / PI, angle, (angle * 180) / PI);

    if (ray_angle < PI/2 || ray_angle > (3*PI)/2)
        cat = (TILE_SIZE * ((int)(player_pt.x / TILE_SIZE) + 1)) - player_pt.x;
    else
        cat = player_pt.x - (TILE_SIZE * (int)(player_pt.x / TILE_SIZE));

    // printf("x = %f\ncat = %f\n", player_pt.x, cat);

    while (!found_wall)
    {
        if (ray_angle == PI || ray_angle == 0)
            ht = cat;
        else if (ray_angle == PI/2 || ray_angle == (3*PI)/2)
        {
            wall_pt.x = INT_MAX;
            wall_pt.y = INT_MAX;
            *ray_lenght = INT_MAX;
            return (wall_pt);
        }
        else
            ht = cat / cos(angle);

        *ray_lenght += ht;

        // printf("ht = %f\n", ht);
        if (ray_angle <= PI/2)
        {
            wall_pt.y = player_pt.y - sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x + cat;
            // printf("Q1\n");
        }
        else if (ray_angle <= PI && ray_angle > PI/2)
        {
            wall_pt.y = player_pt.y - sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x - cat;
            // printf("Q2\n");
        }
        else if (ray_angle > PI && ray_angle <= (3*PI)/2)
        {
            wall_pt.y = player_pt.y + sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x - cat;
            // printf("Q3\n");
        }
        else if (ray_angle > (3*PI)/2)
        {
            wall_pt.y = player_pt.y + sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x + cat;
            // printf("Q4\n");
        }

        if(wall_pt.y > mlx->map->height || wall_pt.y < 0)
        {
            wall_pt.x = INT_MAX;
            wall_pt.y = INT_MAX;
            *ray_lenght = INT_MAX;
            return (wall_pt);
        }
        
        if (((ray_angle < PI/2 || ray_angle > (3*PI)/2) && is_in_wall(map, wall_pt.x + 1, wall_pt.y, mlx)) ||
            ((ray_angle < (3*PI)/2 && ray_angle > PI/2) && is_in_wall(map, wall_pt.x - 1, wall_pt.y, mlx)))
        {
            found_wall = 1;
        }
        else
        {
            cat = TILE_SIZE;
            player_pt = wall_pt;
        }
        
        // printf("horizontal_intersection -> (%f, %f)\n", wall_pt.x, wall_pt.y);
    }
    

    // printf("is in wall = %d\n", is_in_wall(map, TILE_SIZE * 2.5, TILE_SIZE - 1, mlx));
        

    

    return wall_pt;
}

t_point calculate_rayend(t_mlx *mlx, char **map, t_point player_pt, double angle)
{
    t_point h_wall;
    t_point v_wall;
    double v_ray;
    double h_ray;

    h_wall.x = 0;
    h_wall.y = 0;
    v_wall.x = 0;
    v_wall.y = 0;
    v_ray = 0;
    h_ray = 0;

    h_wall = get_h_wall_v(mlx, map, player_pt, angle, &h_ray);
    v_wall = get_v_wall_v(mlx, map, player_pt, angle, &v_ray);
    if(h_ray < v_ray)
        return h_wall;
    else
        return v_wall;
}

t_ray *calculate_ray_lenght(t_mlx *mlx, char **map, t_point player_pt, double angle, int *hits_vertical)
{
    t_point h_wall;
    t_point v_wall;
    double  v_ray;
    double  h_ray;
    t_ray   *ray = malloc(sizeof(t_ray));

    // h_wall.x = 0;
    // h_wall.y = 0;
    // v_wall.x = 0;
    // v_wall.y = 0;
    // v_ray = 0;
    // h_ray = 0;
    h_wall = get_h_wall_v(mlx, map, player_pt, angle, &h_ray);
    v_wall = get_v_wall_v(mlx, map, player_pt, angle, &v_ray);
    if (h_ray < v_ray)
    {
        *hits_vertical = 0;
        ray->ray_length = h_ray;
        if (angle < PI)
            ray->wall_orientation = 'N';
        else
            ray->wall_orientation = 'S';
        ray->tile_hit_point = (int)h_wall.x % TILE_SIZE;
        return ray;
    }
    else
    {
        *hits_vertical = 1;
        ray->ray_length = v_ray;
        if (angle < (3*PI)/2 && angle > PI/2)
            ray->wall_orientation = 'W';
        else
            ray->wall_orientation = 'E';
        ray->tile_hit_point = (int)v_wall.y % TILE_SIZE;
        return ray;
    }
}


uint32_t apply_distance_effect(uint32_t base_color, double distance) 
{
    double max_dist = MAX_DISTANCE;
    double intensity = 1.0 - (distance / max_dist);
    
    if (intensity < 0.1)
        intensity = 0.1;
    
    uint32_t r = (base_color >> 8) & (uint32_t)0xFF;
    uint32_t g = (base_color >> 16) & (uint32_t)0xFF;
    uint32_t b = (base_color >> 24) & (uint32_t)0xFF;
    
    r = (uint32_t)(r * intensity);
    g = (uint32_t)(g * intensity);
    b = (uint32_t)(b * intensity);
    
    // return (r << 16) | (g << 8) | b;
    return (uint32_t)rgb(r, g, b, 255);
}

uint32_t re_apply_distance_effect(uint32_t base_color, double distance) 
{
    double max_dist = MAX_DISTANCE;
    double intensity = 1.0 - (distance / max_dist);
    
    if (intensity < 0.1) // Impedisce che il colore diventi completamente nero
        intensity = 0.1;
    
    // Estrazione corretta dei canali
    uint32_t a = (base_color >> 24) & 0xFF;  // Alpha
    uint32_t r = (base_color >> 16) & 0xFF;  // Rosso
    uint32_t g = (base_color >> 8)  & 0xFF;  // Verde
    uint32_t b = (base_color)       & 0xFF;  // Blu
    
    // Modifica dei valori in base alla distanza
    r = (uint32_t)(r * intensity);
    g = (uint32_t)(g * intensity);
    b = (uint32_t)(b * intensity);
    
    // Ricomposizione del colore in uint32_t
    return (a << 24) | (r << 16) | (g << 8) | b;
}




void    miini(t_mlx *mlx)
{
    int i = 0;
    int j = 0;
    int rdx = mlx->player->x_player - 100;
    int rdy = mlx->player->y_player - 100;
    while (j <= 200)
    {
        i = 0;
        rdx = mlx->player->x_player - 100;
        while (i <= 200)
        {
            if (mlx->cube->map[(int)(rdy / TILE_SIZE)][(int)(rdx / TILE_SIZE)] == '1')
                mlx_put_pixel(mlx->img, i, j, rgb(255, 0, 0, 255));
            else
                mlx_put_pixel(mlx->img, i, j, rgb(255, 0, 0, 100));
            i++;
            rdx++;
        }
        j++;
        rdy++;
    }
}

int    ft_counter(int n)
{
    int    count;

    count = 0;
    if (n == 0)
        return (1);
    if (n < 0)
    {
        count++;
        n *= -1;
    }
    while (n)
    {
        n /= 10;
        count++;
    }
    return (count);
}

char    *ft_itoa(int n)
{
    int        len;
    char    *r;

    if (n == -2147483648)
        return (strdup("-2147483648"));
    len = ft_counter(n);
    r = (char *)malloc((len + 1) * sizeof(char));
    if (r == NULL)
        return (NULL);
    r[len] = '\0';
    len--;
    if (n == 0)
        r[0] = '0';
    if (n < 0)
    {
        n *= -1;
        r[0] = '-';
    }
    while (n)
    {
        r[len] = (n % 10) + 48;
        len--;
        n /= 10;
    }
    return (r);
}
double get_delta_time()
{
    static double last_time = 0;
    struct timeval time;
    gettimeofday(&time, NULL);
    double current_time = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
    
    double delta = (current_time - last_time) / 1000.0;
    last_time = current_time;

    return delta;  // Time per frame in seconds
}

void    re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    int    index;

    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
    {
        index = (y * img->width + x) * 4;
        img->pixels[index + 3] = (color >> 24) & 0xFF; // b
        img->pixels[index + 2] = (color >> 16) & 0xFF; // g    
        img->pixels[index + 1] = (color >> 8) & 0xFF; // r
        img->pixels[index + 0] = (color) & 0xFF;
    }
    //argb bgra
}

void minimap(t_mlx *mlx)
{
    int center_x = 192;
    int center_y = 192;
    float scale = (float)mlx->minimap_scale;
    static mlx_image_t *pre;
    static mlx_image_t *prev;
    float rot_angle = mlx->player->rot_angle - (PI/2);
    int map_pixel_width = mlx->map->width * TILE_SIZE;
    int map_pixel_height = mlx->map->height * TILE_SIZE;

    t_point tip = {
        192 - cos(mlx->player->rot_angle) * (128),
        192 - sin(mlx->player->rot_angle) * (128)
    };

    float cos_angle = cos(-rot_angle);
    float sin_angle = sin(-rot_angle);
    draw_filled_circle(mlx, 192, 192, 135, rgb(0, 0, 0, 255));
    for (int y = 64; y < 320; y++)
    {
        for (int x = 64; x < 320; x++)
        {
            
            int dx = x - center_x;
            int dy = y - center_y;
            
            if (dx*dx + dy*dy > 128*128) 
                continue;

            float rot_x = dx * cos_angle - dy * sin_angle;
            float rot_y = dx * sin_angle + dy * cos_angle;

            int world_x = mlx->player->x_player + (rot_x * scale);
            int world_y = mlx->player->y_player + (rot_y * scale);

            world_x = fmax(0, fmin(world_x, map_pixel_width - 1));
            world_y = fmax(0, fmin(world_y, map_pixel_height - 1));

            int tile_x = world_x / TILE_SIZE;
            int tile_y = world_y / TILE_SIZE;

            if (tile_x < 0 || tile_x >= mlx->map->width/TILE_SIZE || 
                tile_y < 0 || tile_y >= mlx->map->height/TILE_SIZE)
            {
                mlx_put_pixel(mlx->img, x, y, rgb(0, 0, 0, 255));
                continue;
            }

            char cell = mlx->cube->map[tile_y][tile_x];
            if (cell == '0' || strchr("NSEW", cell)) {
                mlx_put_pixel(mlx->img, x, y, rgb(57, 0, 153, 255));
            // } else if (cell == ' ') {
            //     mlx_put_pixel(mlx->img, x, y, rgb(255, 221, 74, 255));
            } else {
                mlx_put_pixel(mlx->img, x, y, rgb(255, 16, 31, 255));
            }
        }
    }

    // Disegna direzione player fissa (verde)
   
    draw_filled_circle(mlx, tip.x, tip.y, 10, rgb(0, 0, 0, 255));
    if (pre)
        mlx_delete_image(mlx->mlx_cnx, pre);
    pre = mlx_put_string(mlx->mlx_cnx, "N", tip.x - 5, tip.y - 10);
    mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.player, center_x - 10, center_y - 10);
    
    // if (prev)
    //     mlx_delete_image(mlx->mlx_cnx, prev);
    // char *str = ft_itoa(1 / get_delta_time());
    // printf("%s\n", str);
    // prev = mlx_put_string(mlx->mlx_cnx, str, 400, 400);
    // free(str);
    // printf("%p\n", fps);
}


void map_render(void   *param)
{
    t_mlx *mlx;
    int     is_minimap = 0;
    t_point player_pt;
    t_ray   *ray;

    mlx = (t_mlx *)param;
    if (!is_minimap)
    {
        player_pt.x = mlx->player->x_player;
        player_pt.y = mlx->player->y_player;
        double angle_start = mlx->player->rot_angle + PI/6;
        if(angle_start < 0)
            angle_start += 2*PI;
        else if (angle_start > 2*PI)
            angle_start -= 2*PI;
        
        double c = (256) * (128 * 80);
        int i = 0;
        double ray_length = 0;
        double ray_pixels = 0;
        mlx_image_t *sky_image = mlx->graphics.sky_image;
        double time = mlx_get_time();
        while (i < 2560)
        {
            int hits_vertical = -1;
            ray = calculate_ray_lenght(mlx, mlx->cube->map, player_pt, angle_start, &hits_vertical);
            double delta_angle = angle_start - mlx->player->rot_angle;
            ray_pixels = c / (ray->ray_length * cos(delta_angle));
            int wall_start = (1280 - ray_pixels) / 2;
            int wall_end = wall_start + ray_pixels;
            int color = 0;
            int ray_colors[1280];
            if (ray->wall_orientation == 'N')
                color = 0x273043;
            else if (ray->wall_orientation == 'S')
                color = 0x9197AE;
            else if (ray->wall_orientation == 'E')
                color = 0xEFF6EE;
            else if (ray->wall_orientation == 'W')
                color = 0xF02D3A;
            int wall_color = apply_distance_effect(color, ray->ray_length);
            int wall_length = wall_end - wall_start;
            double wall_prop = 1280.0 / (double)ray_pixels;
            mlx_image_t *wall_texture;
            wall_texture = NULL;
            if (ray->wall_orientation == 'N')
                wall_texture = mlx->graphics.no_txtr;
            else if (ray->wall_orientation == 'S')
                wall_texture = mlx->graphics.so_txtr;
            else if (ray->wall_orientation == 'E')
                wall_texture = mlx->graphics.ea_txtr;
            else if (ray->wall_orientation == 'W')
                wall_texture = mlx->graphics.we_txtr;
            int image_start_x = 0;     
            int j = 0;
            double text_index;
            text_index = 0;
            uint32_t sky_pixel_color = 0;
            int sky_start = (15360) - ((int)(mlx->player->rot_angle * ((15360)/(2*PI))));
            while(j < wall_start)
            {
                sky_pixel_color = ((uint32_t *)sky_image->pixels)[(j * sky_image->width) + (i) + (sky_start) + ((int)time)];
                re_put_pixel(mlx->img, i, j, sky_pixel_color);
                j++;
            }
            if (ray_pixels > W_HEIGHT)
            {
                text_index = (-wall_start) * wall_prop;
                wall_start = 0;
            }
            while (wall_start < wall_end && wall_start < W_HEIGHT)
            {
                uint32_t texel_color = ((uint32_t *)wall_texture->pixels)[((((int)text_index) * mlx->graphics.no_txtr->width) + ((ray->tile_hit_point) * (mlx->graphics.no_txtr->width / TILE_SIZE)))];
                if (text_index < 1280.0)
                    re_put_pixel(mlx->img, i, wall_start, texel_color);
                wall_start++;
                text_index += wall_prop;
            }
            while(wall_start < W_HEIGHT)
            {
                int floor_color = rgb(136, 152, 178, 255);
                double distanceFactor = 1.0 - (abs(wall_start - (W_HEIGHT / 2)) / ((W_HEIGHT) / 2));
                mlx_put_pixel(mlx->img, i, wall_start, re_apply_distance_effect(floor_color, (distanceFactor * MAX_DISTANCE)));
                wall_start++;
            }
            angle_start -= (PI/3) / 2560;
            if (angle_start < 0)
                angle_start += 2 * PI;
            i++;
        }
    }
    minimap(mlx);
}



int check_wall(t_mlx *mlx, char direction, int *speed)
{
    double x;
    double y;

    x = mlx->player->x_player;
    y = mlx->player->y_player;
    double old_x = x;
    double old_y = y;
    if (direction == 'U') 
    {
        x += cos(mlx->player->rot_angle) * (*speed + 200);
        y -= sin(mlx->player->rot_angle) * (*speed + 200);
    }
    else if (direction == 'D')
    {
        x -= cos(mlx->player->rot_angle) * (*speed + 200);
        y += sin(mlx->player->rot_angle) * (*speed + 200);
    }
    else if (direction == 'L') 
    {
        x += cos(mlx->player->rot_angle + PI / 2) * (*speed + 200);
        y -= sin(mlx->player->rot_angle + PI / 2) * (*speed + 200);
    }
    else if (direction == 'R') 
    {
        x += cos(mlx->player->rot_angle - PI / 2) * (*speed + 200);
        y -= sin(mlx->player->rot_angle - PI / 2) * (*speed + 200);
    }
    t_point average1, average2, average3;
    average1.x = old_x + ((x - old_x) / 4);
    average1.y = old_y + ((y - old_y) / 4);
    average1.x = old_x + (2 * ((x - old_x) / 4));
    average1.y = old_y + (2 * ((y - old_y) / 4));
    average1.x = old_x + (3 * ((x - old_x) / 4));
    average1.y = old_y + (3 * ((y - old_y) / 4));

    if(is_in_wall(mlx->cube->map, x, y, mlx))
    if(is_in_wall(mlx->cube->map, x, y, mlx) || is_in_wall(mlx->cube->map, average1.x, average1.y, mlx)
        || is_in_wall(mlx->cube->map, average2.x, average2.y, mlx) || is_in_wall(mlx->cube->map, average3.x, average3.y, mlx))
    {
        if (!is_in_wall(mlx->cube->map, x, mlx->player->y_player, mlx))
            mlx->player->x_player += (x - mlx->player->x_player) / 2;
        if (!is_in_wall(mlx->cube->map, mlx->player->x_player, y, mlx))
            mlx->player->y_player += (y - mlx->player->y_player) / 2; 
        return 1;
    }
    if (old_x/TILE_SIZE != x/TILE_SIZE && old_y/TILE_SIZE != y/TILE_SIZE)
        return (check_diagonal(mlx->cube->map, x/TILE_SIZE, y/TILE_SIZE, mlx));
    return 0;
}



void    move_player(t_mlx *mlx, char direction, int *speed)
{
    if (check_wall(mlx, direction, speed))
        return ;
    if (direction == 'U') 
    {
        mlx->player->x_player += cos(mlx->player->rot_angle) * (*speed);
        mlx->player->y_player -= sin(mlx->player->rot_angle) * (*speed);
    }
    else if (direction == 'D')
    {
        mlx->player->x_player -= cos(mlx->player->rot_angle) * (*speed);
        mlx->player->y_player += sin(mlx->player->rot_angle) * (*speed);
    }
    else if (direction == 'L') 
    {
        mlx->player->x_player += cos(mlx->player->rot_angle + PI / 2) * (*speed);
        mlx->player->y_player -= sin(mlx->player->rot_angle + PI / 2) * (*speed);
    }
    else if (direction == 'R') 
    {
        mlx->player->x_player += cos(mlx->player->rot_angle - PI / 2) * (*speed);
        mlx->player->y_player -= sin(mlx->player->rot_angle - PI / 2) * (*speed);
    }
}

int	destroy_handler(t_mlx *mlx)
{
	exit(0);
	return (0);
}

void	keydown_handler(void *param)
{
    t_mlx *mlx;
    int speed;

    speed = SPEED;
    mlx = (t_mlx *)param;
    mlx->minimap_scale = MINIMAP_SCALE;
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_LEFT_SHIFT))
    {
        speed = 400;
        mlx->minimap_scale = MINIMAP_SCALE * 1.15;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_ESCAPE))
        destroy_handler(mlx);
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_A))
        move_player(mlx, 'L', &speed);
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_W))
        move_player(mlx, 'U', &speed);
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_D))
        move_player(mlx, 'R', &speed);
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_S))
        move_player(mlx, 'D', &speed);
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_LEFT))
    {
        mlx->player->rot_angle += PI / 36;
        if (mlx->player->rot_angle >= 2*PI)
            mlx->player->rot_angle -= 2*PI;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_RIGHT))
    {
        mlx->player->rot_angle -= PI / 36;
        if (mlx->player->rot_angle < 0)
            mlx->player->rot_angle += 2*PI;
    }
    // map_render(mlx);
}

int	close_win(int keycode, t_mlx *mlx)
{
    int k = keycode;

    k = 0;
	return (0);
}

void    player_infos(t_cube *cube, int *p_x, int *p_y, char *p_or)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(cube->map[i])
    {
        j = 0;
        while (cube->map[i][j])
        {
            if(cube->map[i][j] == 'N' || cube->map[i][j] == 'S' || cube->map[i][j] == 'E' || cube->map[i][j] == 'W')
            {
                *p_x = j;
                *p_y = i;
                *p_or = cube->map[i][j];
            }
            j++;
        }        
        i++;
    }
}

void player_init(t_mlx *mlx)
{
    int     player_x;
    int     player_y;
    char    player_orientation;
    
    player_x = 0;
    player_y = 0;
    player_orientation = '0';
    if (!mlx || !mlx->player || !mlx->map || !mlx->cube->map)
    {
        puts("heeheeehhe");
        return;
    }
    player_infos(mlx->cube, &player_x, &player_y, &player_orientation);
    mlx->player->x_player = (TILE_SIZE * player_x) + (TILE_SIZE / 2);
    mlx->player->y_player = (TILE_SIZE * player_y) + (TILE_SIZE / 2);
    if (player_orientation == 'N')
        mlx->player->rot_angle = PI/2;
    else if (player_orientation == 'W')
        mlx->player->rot_angle = PI;
    else if (player_orientation == 'S')
        mlx->player->rot_angle = (3*PI)/2;
    else if (player_orientation == 'E')
        mlx->player->rot_angle = 0;
}
void *salloc(int size)
{
    void *alloc;

    alloc = malloc(size);
    if (!alloc)
    {
        printf("MALLOC ERROR\n");
        exit(1);
    }
    return (alloc);
}
void    initializer(t_mlx *mlx, t_cube *cube, int h_tiles, int w_tiles)
{
    // mlx->mlx_cnx = mlx_init();
    // mlx->mlx_cnx = mlx_init( 2560, 1280, "CUB3D", false);
    mlx->mlx_cnx = mlx_init( 1280, 700, "CUB3D", false);
    mlx->img = mlx_new_image(mlx->mlx_cnx, 2560, 1280);
    // mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
    mlx->map = salloc(sizeof(t_map));
    mlx->map->height = h_tiles * TILE_SIZE;
    mlx->map->width = w_tiles * TILE_SIZE;
    mlx->cube = cube;
    mlx->player = salloc(sizeof(t_player));
    mlx->minimap_scale = MINIMAP_SCALE;
    player_init(mlx);
    
}

void    load_graphics(t_mlx *mlx, t_cube *cube)
{
    mlx->graphics.no_txtr = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png(cube->no_tex));
    mlx->graphics.so_txtr = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png(cube->so_tex));
    mlx->graphics.ea_txtr = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png(cube->ea_tex));
    mlx->graphics.we_txtr = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png(cube->we_tex));
    mlx->graphics.sky_image = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png("textures/sky5.png"));
    mlx->graphics.player = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png("textures/player_arrow1.png"));
    mlx->graphics.north = mlx_texture_to_image(mlx->mlx_cnx, mlx_load_png("textures/north.png"));

    mlx_resize_image(mlx->graphics.no_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.so_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.ea_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.we_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.player, 20, 20);
    mlx_resize_image(mlx->graphics.north, 20, 20);
}



int main(int ac, char **av)
{
    t_cube  cube;
    (void)ac;
    init_cube(&cube);
    cube.file_name = ft_strdup(av[1]);
    if (check_map_name(cube.file_name) == 1)
    {
        printf("map name error\n");
        return (1);
    }
    cube.fd = open(cube.file_name, O_RDONLY);
    if (read_file(&cube) == 1)
        return (1);
    int i= 0;
    if (parse_file(&cube) == 1)
        return (1);
    if (check_map(&cube) == 1)
        return (1);
    i = 0;
    int height_tiles = 0;
    int width_tiles = 0;
    while(cube.map[i])
    {
        printf("[%s]\n", cube.map[i]);
        if(ft_strlen(cube.map[i]) > width_tiles)
            width_tiles = ft_strlen(cube.map[i]);
        i++;
    }
    height_tiles = i;
    // EXECUTION
    t_mlx   *mlx;
    
    mlx = salloc(sizeof(t_mlx));
    initializer(mlx, &cube, height_tiles, width_tiles);
    load_graphics(mlx, &cube);
    mlx_image_to_window(mlx->mlx_cnx, mlx->img, 0, 0);
    
    mlx_loop_hook(mlx->mlx_cnx, keydown_handler, mlx);
    mlx_loop_hook(mlx->mlx_cnx, map_render, mlx);
    mlx_loop(mlx->mlx_cnx);
}
