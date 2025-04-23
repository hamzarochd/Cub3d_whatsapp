#include "cub3d.h"

uint32_t    rgb(int r, int g, int b, int a)
{
    return (((r & 0xFF) << 24) | ((g & 0xFF) << 16)
        | ((b & 0xFF) << 8) | (a & 0xFF));
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

int is_digit(char i)
{
    if (i < '0' && i > '9')
        return (0);
    return (1);
}

char    *color_join(char    **splitted)
{
    char    *res;
    int i;
    int j;

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
    i = 0;
    // j = 0;
    // while(res[i])
    // {
        
    //     if (res[i] == ',')
    //         j++;
    // }
    // if (j)
    return (res);
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
    while (pixels)
    {
        mlx_put_pixel(mlx->img, pixel_pt.x, pixel_pt.y, rgb(255, 255, 255, 255));
        pixel_pt.x += delta_x;
        pixel_pt.y += delta_y;
        pixels--;
    }
    return 0;
}

void draw_filled_circle(t_mlx *mlx, int x_center, int y_center, int radius, int color)
{
    int x, y;

    for (y = y_center - radius; y <= y_center + radius; y++)
    {
        for (x = x_center - radius; x <= x_center + radius; x++)
        {
            if ((x - x_center) * (x - x_center) + (y - y_center) * (y - y_center) <= radius * radius)
            {
                mlx_put_pixel(mlx->img, x, y, color);
            }
        }
    }
}

int check_diagonal(char **map, int xtile, int ytile, t_mlx *mlx)
{

    int player_x;
    int player_y;

    player_x = mlx->player.x_player/TILE_SIZE;
    player_y = mlx->player.y_player/TILE_SIZE;
    if ((map[player_y][xtile] == '1' && map[ytile][player_x] == '1') ||
        (map[player_y][xtile] == 'D' && map[ytile][player_x] == 'D'))
        return 1;
    return 0;
}

int is_in_door(char **map, double x, double y, t_mlx *mlx)
{
    int map_x;
    int map_y;

    map_x = x / TILE_SIZE;
    map_y = y / TILE_SIZE;
    if (map_x < (mlx->map.width / TILE_SIZE) && map_y < (mlx->map.height / TILE_SIZE)
        && map_x >= 0 && map_y >= 0)
    {
        if(map[map_y][map_x] == 'D')
            return 1;
        else
            return 0;
    }
    return 0;
}

int is_in_wall(char **map, double x, double y, t_mlx *mlx)
{
    int map_x;
    int map_y;

    map_x = x / TILE_SIZE;
    map_y = y / TILE_SIZE;
    if (map_x < (mlx->map.width / TILE_SIZE) && map_y < (mlx->map.height / TILE_SIZE)
        && map_x >= 0 && map_y >= 0)
    {
        if(map[map_y][map_x] == '1' || map[map_y][map_x] == 'D')
            return 1;
        else
            return 0;
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
    double scaling_factor;
    t_point unit_vec;


    scaling_factor = 0;
    wall_pt.x = 0;
    wall_pt.y = 0;
    unit_vec.x = 0;
    unit_vec.y = 0;
    angle = 0;
    next_wall_y = 0;
    found_wall = 0;
    ht = 0;
    quarter = 0;
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
    if (ray_angle < PI)
        cat = player_pt.y - (TILE_SIZE * (int)(player_pt.y / TILE_SIZE));
    else
        cat = (TILE_SIZE * ((int)(player_pt.y / TILE_SIZE) + 1)) - player_pt.y;
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
        if (ray_angle <= PI/2)
        {
            wall_pt.y = player_pt.y - cat;
            wall_pt.x = player_pt.x + sqrt((ht * ht) - (cat * cat));
        }
        else if (ray_angle < PI && ray_angle > PI/2)
        {
            wall_pt.y = player_pt.y - cat;
            wall_pt.x = player_pt.x - sqrt((ht * ht) - (cat * cat));
        }
        else if (ray_angle > PI && ray_angle <= (3*PI)/2)
        {
            wall_pt.y = player_pt.y + cat;
            wall_pt.x = player_pt.x - sqrt((ht * ht) - (cat * cat));
        }
        else if (ray_angle > (3*PI)/2)
        {
            wall_pt.y = player_pt.y + cat;
            wall_pt.x = player_pt.x + sqrt((ht * ht) - (cat * cat));
        }
        if(wall_pt.x > mlx->map.width || wall_pt.x < 0)
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
    }
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
    if (ray_angle < PI/2 || ray_angle > (3*PI)/2)
        cat = (TILE_SIZE * ((int)(player_pt.x / TILE_SIZE) + 1)) - player_pt.x;
    else
        cat = player_pt.x - (TILE_SIZE * (int)(player_pt.x / TILE_SIZE));
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
        if (ray_angle <= PI/2)
        {
            wall_pt.y = player_pt.y - sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x + cat;
        }
        else if (ray_angle <= PI && ray_angle > PI/2)
        {
            wall_pt.y = player_pt.y - sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x - cat;
        }
        else if (ray_angle > PI && ray_angle <= (3*PI)/2)
        {
            wall_pt.y = player_pt.y + sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x - cat;
        }
        else if (ray_angle > (3*PI)/2)
        {
            wall_pt.y = player_pt.y + sqrt((ht * ht) - (cat * cat));
            wall_pt.x = player_pt.x + cat;
        }

        if(wall_pt.y > mlx->map.height || wall_pt.y < 0)
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
    }
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

t_ray calculate_ray_lenght(t_mlx *mlx, char **map, t_point player_pt, double angle)
{
    t_point h_wall;
    t_point v_wall;
    double  v_ray;
    double  h_ray;
    t_ray   ray;

    h_wall = get_h_wall_v(mlx, map, player_pt, angle, &h_ray);
    v_wall = get_v_wall_v(mlx, map, player_pt, angle, &v_ray);
    ray.is_door = 0;
    ray.ray_pixels = 0;
    if (h_ray < v_ray)
    {
        ray.ray_length = h_ray;
        ray.tile_hit_point = (int)h_wall.x % TILE_SIZE;
        if (angle < PI)
            ray.wall_orientation = 'N';
        else
            ray.wall_orientation = 'S';
        if (ray.wall_orientation == 'S')
            ray.tile_hit_point = TILE_SIZE - ray.tile_hit_point;
        if ((ray.wall_orientation == 'N' && is_in_door(map, h_wall.x, h_wall.y - 1, mlx))
            || (ray.wall_orientation == 'S' && is_in_door(map, h_wall.x, h_wall.y + 1, mlx)))
            ray.is_door = 1;
        return ray;
    }
    else
    {
        ray.ray_length = v_ray;
        ray.tile_hit_point = (int)v_wall.y % TILE_SIZE;
        if (angle < (3*PI)/2 && angle > PI/2)
            ray.wall_orientation = 'W';
        else
            ray.wall_orientation = 'E';
        if (ray.wall_orientation == 'W')
            ray.tile_hit_point = TILE_SIZE - ray.tile_hit_point;
        if ((ray.wall_orientation == 'W' && is_in_door(map, v_wall.x - 1, v_wall.y, mlx))
            || (ray.wall_orientation == 'E' && is_in_door(map, v_wall.x + 1, v_wall.y, mlx)))
            ray.is_door = 1;
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
    return (uint32_t)rgb(r, g, b, 255);
}

uint32_t re_apply_distance_effect(uint32_t base_color, double distance) 
{
    double max_dist = MAX_DISTANCE;
    double intensity = 1.0 - (distance / max_dist);
    
    if (intensity < 0.1)
        intensity = 0.1;
    uint32_t a = (base_color >> 24) & 0xFF; 
    uint32_t r = (base_color >> 16) & 0xFF; 
    uint32_t g = (base_color >> 8)  & 0xFF;
    uint32_t b = (base_color)       & 0xFF;
    r = (uint32_t)(r * intensity);
    g = (uint32_t)(g * intensity);
    b = (uint32_t)(b * intensity);
    return (a << 24) | (r << 16) | (g << 8) | b;
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

    return delta;
}

void    re_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    int    index;

    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
    {
        index = (y * img->width + x) * 4;
        img->pixels[index + 3] = (color >> 24) & 0xFF; 
        img->pixels[index + 2] = (color >> 16) & 0xFF;   
        img->pixels[index + 1] = (color >> 8) & 0xFF;
        img->pixels[index + 0] = (color) & 0xFF;
    }
}

void minimap(t_mlx *mlx)
{
    int center_x = 192;
    int center_y = 192;
    float scale = (float)mlx->minimap_scale;
    static mlx_image_t *pre;
    static mlx_image_t *prev;
    float rot_angle = mlx->player.rot_angle - (PI/2);
    int map_pixel_width = mlx->map.width * TILE_SIZE;
    int map_pixel_height = mlx->map.height * TILE_SIZE;

    t_point tip = {
        192 - cos(mlx->player.rot_angle) * (128),
        192 - sin(mlx->player.rot_angle) * (128)
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
            int world_x = mlx->player.x_player + (rot_x * scale);
            int world_y = mlx->player.y_player + (rot_y * scale);
            world_x = fmax(0, fmin(world_x, map_pixel_width - 1));
            world_y = fmax(0, fmin(world_y, map_pixel_height - 1));
            int tile_x = world_x / TILE_SIZE;
            int tile_y = world_y / TILE_SIZE;
            if (tile_x < 0 || tile_x >= mlx->map.width/TILE_SIZE || 
                tile_y < 0 || tile_y >= mlx->map.height/TILE_SIZE)
            {
                mlx_put_pixel(mlx->img, x, y, rgb(0, 0, 0, 255));
                continue;
            }
            char cell = mlx->cube->map[tile_y][tile_x];
            if (cell == '0' || strchr("NSEW", cell))
                mlx_put_pixel(mlx->img, x, y, rgb(211, 211, 211, 255));
            else if (cell == 'O')
                mlx_put_pixel(mlx->img, x, y, rgb(179, 158, 106, 255));
            else if (cell == 'D')
                mlx_put_pixel(mlx->img, x, y, rgb(103, 73, 40, 255));
            else
                mlx_put_pixel(mlx->img, x, y, rgb(108, 108, 108, 255));
        }
    }

    draw_filled_circle(mlx, tip.x, tip.y, 10, rgb(0, 0, 0, 255));
    if (pre)
        mlx_delete_image(mlx->mlx_cnx, pre);
    pre = mlx_put_string(mlx->mlx_cnx, "N", tip.x - 5, tip.y - 10);
    mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.player, center_x - 10, center_y - 10);
}


mlx_image_t *define_wall_tex(int is_door, char wall_orientation, t_graphics graphics)
{
    if (is_door)
        return (graphics.door_txtr);
    else
    {
        if (wall_orientation == 'N')
            return (graphics.no_txtr);
        else if (wall_orientation == 'S')
            return (graphics.so_txtr);
        else if (wall_orientation == 'E')
            return (graphics.ea_txtr);
        else 
            return (graphics.we_txtr);
    }
}


void put_wall(t_mlx *mlx, int i, int *j, t_wall wall)
{
    int k;
    uint32_t index;
    uint32_t tex_width;
    uint32_t tex_height;
    
    tex_width = wall.wall_texture->width;
    tex_height = wall.wall_texture->height;
    wall.tex.texel_x = (wall.ray->tile_hit_point) * (tex_width / TILE_SIZE);
    wall.tex.texel_x = wall.tex.texel_x % tex_width;
    index = wall.tex.texel_x;
    k = *j;
    while (k < wall.wall_end)
    {
        wall.tex.texel_y = ((int)wall.tex.tex_index) * tex_width;
        wall.tex.texel_y = wall.tex.texel_y % (tex_width * tex_height);
        index = (index + wall.tex.texel_y) % (tex_width * tex_height); 
        wall.tex.texel_color = ((uint32_t *)(wall.wall_texture->pixels))[(wall.tex.texel_y + wall.tex.texel_x)];
        re_put_pixel(mlx->img, i, k, wall.tex.texel_color);
        k++;
        wall.tex.tex_index += wall.wall_prop;
    }
    *j = k;
}


void put_ceiling(t_mlx *mlx, int i, int *j,int wall_start)
{
    // uint32_t sky_pixel_color = 0;
    // int sky_start = (15360) - ((int)(mlx->player.rot_angle * ((15360)/(2*PI))));
    int k;

    k = *j;
    while(k < wall_start)
    {

        ///// get sky color from parsing
        // uint32_t pixel_offset = ((*j) * sky_image->width) + i + sky_start + (int)time;
        // sky_pixel_color = ((uint32_t *)sky_image->pixels)[pixel_offset];
        mlx_put_pixel(mlx->img, i, k, rgb(136, 152, 178, 255));
        k++;
    }
    *j = k;
}

void    put_floor(t_mlx *mlx, int i, int *j)
{
    int k;

    k = *j;
    while(k < W_HEIGHT)
    {
        ////// get color from parsing
        int floor_color = rgb(136, 152, 178, 255);
        mlx_put_pixel(mlx->img, i, k, floor_color);
        k++;
    }
    *j = k;     
}

t_wall  get_wall(t_mlx *mlx, t_ray *ray, double ray_pixels)
{
    t_wall wall;
    
    wall.wall_start = (W_HEIGHT - ray_pixels) / 2;
    wall.wall_end = wall.wall_start + ray_pixels;
    wall.wall_prop = W_HEIGHT / (double)ray_pixels;
    wall.wall_texture = define_wall_tex(ray->is_door, ray->wall_orientation, mlx->graphics);  
    wall.tex.tex_index = 0;
    return (wall);
}

void    normmalize_angle(double *angle)
{
    if(*angle < 0)
        *angle += 2*PI;
    else if (*angle > 2*PI)
        *angle -= 2*PI;
}


void map_render(void   *param)
{
    t_mlx   *mlx;
    t_ray   ray;
    t_point player_pt;
    t_rendex    r;
    t_wall wall;

    mlx = (t_mlx *)param;
    player_pt.x = mlx->player.x_player;
    player_pt.y = mlx->player.y_player;
    
    r.angle_start = mlx->player.rot_angle + PI/6;
    normmalize_angle(&r.angle_start);
    mlx_image_t *sky_image = mlx->graphics.sky_image;
    r.i = 0;
    while (r.i < W_WIDTH)
    {
        ray = calculate_ray_lenght(mlx, mlx->cube->map, player_pt, r.angle_start);
        double delta_angle = r.angle_start - mlx->player.rot_angle;
        ray.ray_pixels = mlx->wall_const / (ray.ray_length * cos(delta_angle));
        wall = get_wall(mlx, &ray, ray.ray_pixels);
        r.j = 0;
        put_ceiling(mlx, r.i, &r.j, wall.wall_start);
        if (ray.ray_pixels > W_HEIGHT)
        {
            wall.tex.tex_index = (-wall.wall_start) * wall.wall_prop;
            r.j = 0;
        }
        wall.ray = &ray;
        put_wall(mlx, r.i, &r.j, wall);
        put_floor(mlx, r.i, &r.j);
        r.angle_start -= (PI/3) / W_WIDTH;
        normmalize_angle(&r.angle_start);
        r.i++;
    }
    minimap(mlx);
}

int check_wall(t_mlx *mlx, char direction, int *speed)
{
    double x;
    double y;

    x = mlx->player.x_player;
    y = mlx->player.y_player;
    double old_x = x;
    double old_y = y;
    if (direction == 'U') 
    {
        x += cos(mlx->player.rot_angle) * (*speed + 200);
        y -= sin(mlx->player.rot_angle) * (*speed + 200);
    }
    else if (direction == 'D')
    {
        x -= cos(mlx->player.rot_angle) * (*speed + 200);
        y += sin(mlx->player.rot_angle) * (*speed + 200);
    }
    else if (direction == 'L') 
    {
        x += cos(mlx->player.rot_angle + PI / 2) * (*speed + 200);
        y -= sin(mlx->player.rot_angle + PI / 2) * (*speed + 200);
    }
    else if (direction == 'R') 
    {
        x += cos(mlx->player.rot_angle - PI / 2) * (*speed + 200);
        y -= sin(mlx->player.rot_angle - PI / 2) * (*speed + 200);
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
        if (!is_in_wall(mlx->cube->map, x, mlx->player.y_player, mlx))
            mlx->player.x_player += (x - mlx->player.x_player) / 2;
        if (!is_in_wall(mlx->cube->map, mlx->player.x_player, y, mlx))
            mlx->player.y_player += (y - mlx->player.y_player) / 2; 
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
        mlx->player.x_player += cos(mlx->player.rot_angle) * (*speed);
        mlx->player.y_player -= sin(mlx->player.rot_angle) * (*speed);
    }
    else if (direction == 'D')
    {
        mlx->player.x_player -= cos(mlx->player.rot_angle) * (*speed);
        mlx->player.y_player += sin(mlx->player.rot_angle) * (*speed);
    }
    else if (direction == 'L') 
    {
        mlx->player.x_player += cos(mlx->player.rot_angle + PI / 2) * (*speed);
        mlx->player.y_player -= sin(mlx->player.rot_angle + PI / 2) * (*speed);
    }
    else if (direction == 'R') 
    {
        mlx->player.x_player += cos(mlx->player.rot_angle - PI / 2) * (*speed);
        mlx->player.y_player -= sin(mlx->player.rot_angle - PI / 2) * (*speed);
    }
}

int	destroy_handler(t_mlx *mlx)
{
	exit(0);
	return (0);
}


void    mouse_handler(double mouse_x, double mouse_y, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    const double center_x = W_WIDTH/2;
    double delta_x = mouse_x - center_x;
    // double sensibility = 0.000385;
    // double sensibility = 0.003;

    mlx->player.rot_angle -= (PI/4) * (delta_x/center_x);
    if (mlx->player.rot_angle >= 2*PI)
        mlx->player.rot_angle -= 2*PI;
    if (mlx->player.rot_angle < 0)
        mlx->player.rot_angle += 2*PI;

    mlx_set_mouse_pos(mlx->mlx_cnx, W_WIDTH/2, W_HEIGHT/2);
}



void    open_door(struct mlx_key_data keydata, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    char **map = mlx->cube->map;
    int player_x = mlx->player.x_player / TILE_SIZE;
    int player_y = mlx->player.y_player / TILE_SIZE;
    if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
    {
        if (mlx->player.rot_angle >= PI/4 && mlx->player.rot_angle < 3*(PI/4))
        {
            if (map[player_y - 1][player_x] == 'D')
                map[player_y - 1][player_x] = 'O';
            else if (map[player_y - 1][player_x] == 'O')
                map[player_y - 1][player_x] = 'D';
        }
        else if (mlx->player.rot_angle >= 3*(PI/4) && mlx->player.rot_angle < 5*(PI/4))
        {
            if (map[player_y][player_x - 1] == 'D')
                map[player_y][player_x - 1] = 'O';
            else if (map[player_y][player_x - 1] == 'O')
                map[player_y][player_x - 1] = 'D';
        }
        else if (mlx->player.rot_angle >= 5*(PI/4) && mlx->player.rot_angle < 7*(PI/4))
        {
            if (map[player_y + 1][player_x] == 'D')
                map[player_y + 1][player_x] = 'O';
            else if (map[player_y + 1][player_x] == 'O')
                map[player_y + 1][player_x] = 'D';
        }
        else
        {
            if (map[player_y][player_x + 1] == 'D')
                map[player_y][player_x + 1] = 'O';
            else if (map[player_y][player_x + 1] == 'O')
                map[player_y][player_x + 1] = 'D';
        }
    }
    if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
        mlx->is_reloading = 1;
    
}


void	keydown_handler(void *param)
{
    t_mlx *mlx;
    int speed;
    int moved;

    moved = 0;
    speed = SPEED;
    mlx = (t_mlx *)param;
    mlx->minimap_scale = MINIMAP_SCALE;
    // mlx_set_cursor_mode(mlx, );
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_LEFT_SHIFT))
    {
        speed = 400;
        mlx->minimap_scale = MINIMAP_SCALE * 1.15;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_ESCAPE))
        destroy_handler(mlx);
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_A))
    {
        move_player(mlx, 'L', &speed);
        moved = 1;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_W))
    {
        move_player(mlx, 'U', &speed);
        moved = 1;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_D))
    {
        move_player(mlx, 'R', &speed);
        moved = 1;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_S))
    {
        move_player(mlx, 'D', &speed);
        moved = 1;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_LEFT))
    {
        mlx->player.rot_angle += PI / 36;
        if (mlx->player.rot_angle >= 2*PI)
            mlx->player.rot_angle -= 2*PI;
    }
    if (mlx_is_key_down(mlx->mlx_cnx, MLX_KEY_RIGHT))
    {
        mlx->player.rot_angle -= PI / 36;
        if (mlx->player.rot_angle < 0)
            mlx->player.rot_angle += 2*PI;
    }
    if (moved)
        mlx->is_walking = 1;
    else 
        mlx->is_walking = 0;
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
    if (!mlx || !mlx->cube->map)
    {
        puts("heeheeehhe"); //change
        return;
    }
    player_infos(mlx->cube, &player_x, &player_y, &player_orientation);
    mlx->player.x_player = (TILE_SIZE * player_x) + (TILE_SIZE / 2);
    mlx->player.y_player = (TILE_SIZE * player_y) + (TILE_SIZE / 2);
    if (player_orientation == 'N')
        mlx->player.rot_angle = PI/2;
    else if (player_orientation == 'W')
        mlx->player.rot_angle = PI;
    else if (player_orientation == 'S')
        mlx->player.rot_angle = (3*PI)/2;
    else if (player_orientation == 'E')
        mlx->player.rot_angle = 0;
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

void set_dimensions(t_cube *cube, int *height_tiles, int *width_tiles)
{
    int i;
    int h;
    int w;

    i = 0;
    h = 0;
    w = 0;
    while(cube->map[i])
    {
        if(ft_strlen(cube->map[i]) > w)
            w = ft_strlen(cube->map[i]);
        i++;
    }
    h = i;
    *height_tiles = h;
    *width_tiles = w;
}

void    initializer(t_mlx *mlx, t_cube *cube)
{
    int h_tiles;
    int w_tiles;

    set_dimensions(cube, &h_tiles, &w_tiles);
    mlx->mlx_cnx = mlx_init( W_WIDTH, W_HEIGHT, "CUB3D", false);
    if (!mlx->mlx_cnx)
        ft_exit(mlx);
    mlx->img = mlx_new_image(mlx->mlx_cnx, W_WIDTH, W_HEIGHT);
    if (!mlx->img)
        ft_exit(mlx);
    mlx->map.height = h_tiles * TILE_SIZE;
    mlx->map.width = w_tiles * TILE_SIZE;
    mlx->cube = cube;
    mlx->minimap_scale = MINIMAP_SCALE;
    mlx->is_walking = 0;
    mlx->is_holding = 0;
    mlx->is_firing = 0;
    mlx->is_reloading = 0;
    mlx->wall_const = (W_HEIGHT / 5) * ((W_HEIGHT / 10) * 80);
    player_init(mlx);
}

void    gun_animation(t_mlx *mlx, int x, int y)
{
    int i;
    int src;
    int dest;

    i = 0;
    // printf("%d\n", 8*y + x);
    // src = (y * GUN_W) + (x * GUN_W);
    src = (x * GUN_W) + ((y * GUN_H) * mlx->graphics.gun_tex->width);
    dest = 0; 

    while (i < GUN_H)
    {
        // dest = i * GUN_W;
        // src = ((y * GUN_H) * (mlx->graphics.gun_tex->width)) + (x * GUN_W);
        memcpy((uint32_t *)mlx->graphics.gun->pixels + dest, (uint32_t *)mlx->graphics.gun_tex->pixels + src, GUN_W * 4);
        src += mlx->graphics.gun_tex->width;
        dest += GUN_W;
        i++;
        // y++;
    } 
}
void    fire_animation(t_mlx *mlx, int x, int y)
{
    int i;
    int src;
    int dest;

    i = 0;
    // src = (y * GUN_W) + (x * GUN_W);
    src = (x * FIRE_W) + ((y * FIRE_H) * mlx->graphics.fire_tex->width);
    dest = 0; 
    // int j = y * FIRE_H;
    while (i < FIRE_H)
    {
        // dest = i * FIRE_W;
        // src = (j * (mlx->graphics.fire_tex->width)) + (x * FIRE_W);
        memcpy((uint32_t *)mlx->graphics.fire->pixels + dest, (uint32_t *)mlx->graphics.fire_tex->pixels + src, FIRE_W * 4);
        src += mlx->graphics.fire_tex->width;
        dest += FIRE_W;
        i++;
        // j++;
    } 
}




// void    reload_frame(t_data *data, int x, int y)
// {
//     int    i;
//     int    j;
//     int    k;
//     int    v_index;
//     int    g_index;

//     i = 0;
//     j = y * RELOAD_H;
//     k = x * RELOAD_W;
//     while (i < RELOAD_H)
//     {
//         g_index = (((j) * data->mlx_data->reload_sheet->width) + (k));
//         v_index = (i * data->mlx_data->reload_view->width);
//         memcpy((uint32_t *)data->mlx_data->reload_view->pixels + v_index,
//             (uint32_t *)data->mlx_data->reload_sheet->pixels + g_index,
//             RELOAD_W * 4);
//         i++;
//         j++;
//     }
// }
void    reload_animation(t_mlx *mlx, int x, int y)
{
    int i;
    int src;
    int dest;

    i = 0;
    // src = (y * GUN_W) + (x * GUN_W);
    src = (x * RELOAD_W) + ((y * RELOAD_H) * mlx->graphics.reload_tex->width);
    dest = 0; 
    // printf("%d\ty %d\n", x, y);
    // int j = y * RELOAD_H;
    while (i < RELOAD_H)
    {
        // dest = i * mlx->graphics.reload->width;
        // src = ((j) * (mlx->graphics.reload_tex->width)) + (x * RELOAD_W);
        // printf("%d\t y %d\t%d\n", dest, mlx->graphics.reload->width,  mlx->graphics.reload->width);
        memcpy(((uint32_t *) mlx->graphics.reload->pixels) + dest, ((uint32_t *) mlx->graphics.reload_tex->pixels) + src, RELOAD_W * 4);
        src += mlx->graphics.reload_tex->width;
        dest += RELOAD_W;
        i++;
        // j++;
    } 
}

void    fire_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
    {
        mlx->is_firing = 1;
        mlx->is_holding = 1;
    }
    if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
    {
        mlx->is_firing = 0;
        mlx->is_holding = 0;
    }
}

void    animation_hook(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    static int gun_i;
    static int fire_i;
    static int reload_i;

    if (mlx->is_walking)
    {
        if (gun_i == 0)
        {
            mlx->graphics.gun->instances[0].enabled = true;
            mlx->graphics.reload->instances[0].enabled = false;
            mlx->graphics.fire->instances[0].enabled = false;
        }
        gun_animation(mlx, gun_i % 8, gun_i / 8);
        gun_i++;
        if (gun_i == 44)
            gun_i = 0;
    }
    if (mlx->is_firing ||  fire_i != 0 || mlx->is_holding)
    {
        if (mlx->is_firing && fire_i)
            fire_i = 0;
        if (fire_i == 0)
        {
            mlx->graphics.gun->instances[0].enabled = false;
            mlx->graphics.reload->instances[0].enabled = false;
            mlx->graphics.fire->instances[0].enabled = true;
            mlx->is_firing = 0;
        }
        fire_animation(mlx, fire_i % 6, fire_i / 6);
        fire_i+=2;
        if (fire_i == 16)
        {
            fire_i = 0;
            mlx->is_firing = 0;
            mlx->graphics.fire->instances[0].enabled = false;
            mlx->graphics.gun->instances[0].enabled = true;
            gun_i = 0;
        }
    }
    if (mlx->is_reloading)
    {
        if (reload_i == 0)
        {
            mlx->graphics.gun->instances[0].enabled = false;
            mlx->graphics.reload->instances[0].enabled = true;
            mlx->graphics.fire->instances[0].enabled = false;
        }
        reload_animation(mlx, reload_i % 8, reload_i / 8);
        reload_i++;
        if (reload_i == 44)
        {
            reload_i = 0;
            mlx->is_reloading = 0;
            mlx->graphics.reload->instances[0].enabled = false;
            mlx->graphics.gun->instances[0].enabled = true;
            gun_i = 0;
        }
    }
}



mlx_image_t *textures_loader(t_mlx *mlx, const char *path)
{
    mlx_texture_t * tmp;
    mlx_image_t *img; 

    tmp =  mlx_load_png(path);
    if (!tmp)
        ft_exit(mlx);
    img = mlx_texture_to_image(mlx->mlx_cnx, tmp);
    if (!img)
        ft_exit(mlx);
    mlx_delete_texture(tmp);
    return (img);
}

void delete_images(t_mlx *mlx)
{
    if (mlx->graphics.no_txtr)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.no_txtr);
    if (mlx->graphics.so_txtr)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.so_txtr);
    if (mlx->graphics.ea_txtr)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.ea_txtr);
    if (mlx->graphics.we_txtr)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.we_txtr);
    if (mlx->graphics.door_txtr)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.door_txtr);
    if (mlx->graphics.sky_image)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.sky_image);
    if (mlx->graphics.player)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.player);
    if (mlx->graphics.gun)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.gun);
    if (mlx->graphics.fire)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.fire);
    if (mlx->graphics.reload)
        mlx_delete_image(mlx->mlx_cnx, mlx->graphics.reload);
}

void free_parsing(t_mlx *mlx)
{
    int i;

    free(mlx->cube->file_name);
    free(mlx->cube->no_tex);
    free(mlx->cube->so_tex);
    free(mlx->cube->we_tex);
    free(mlx->cube->ea_tex);
    free(mlx->cube->floor_color);
    free(mlx->cube->ceiling_color);
    i = 0;
    while (mlx->cube->map[i])
        free(mlx->cube->map[i++]);
    free(mlx->cube->map);
    // free file content


}


void ft_exit(t_mlx *mlx)
{
    delete_images(mlx);
    if (mlx->graphics.gun_tex)
        mlx_delete_texture(mlx->graphics.gun_tex);
    if (mlx->graphics.fire_tex)
        mlx_delete_texture(mlx->graphics.fire_tex);
    if (mlx->graphics.reload_tex)
        mlx_delete_texture(mlx->graphics.reload_tex);
    if (mlx->mlx_cnx)
    {
        mlx_close_window(mlx->mlx_cnx);
        mlx_terminate(mlx->mlx_cnx);
    }
    free_parsing(mlx);
    exit(0);
}

void    load_graphics(t_mlx *mlx, t_cube *cube)
{
    mlx->graphics.no_txtr = textures_loader(mlx, cube->no_tex);
    mlx->graphics.so_txtr = textures_loader(mlx, cube->so_tex);
    mlx->graphics.ea_txtr = textures_loader(mlx, cube->ea_tex);
    mlx->graphics.we_txtr = textures_loader(mlx, cube->we_tex);
    mlx->graphics.door_txtr = textures_loader(mlx, "textures/no1.png");
    mlx->graphics.sky_image = textures_loader(mlx, "textures/sky5.png");
    mlx->graphics.player = textures_loader(mlx, "textures/player_arrow1.png");
    mlx->graphics.fire_tex = mlx_load_png("textures/fire_tex.png");
    mlx->graphics.reload_tex = mlx_load_png("textures/reload_tex.png");
    mlx->graphics.gun_tex = mlx_load_png("textures/gun_tex.png");
    mlx->graphics.gun = mlx_new_image(mlx->mlx_cnx, GUN_W, GUN_H);
    mlx->graphics.fire = mlx_new_image(mlx->mlx_cnx, FIRE_W, FIRE_H);
    mlx->graphics.reload = mlx_new_image(mlx->mlx_cnx, RELOAD_W, RELOAD_H);
    if (!mlx->graphics.fire_tex || !mlx->graphics.gun_tex || !mlx->graphics.reload_tex ||
        !mlx->graphics.fire || !mlx->graphics.gun || !mlx->graphics.reload )
        ft_exit(mlx);
    mlx_resize_image(mlx->graphics.no_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.so_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.ea_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.we_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.door_txtr, W_HEIGHT, W_HEIGHT);
    mlx_resize_image(mlx->graphics.player, 20, 20);
}

void put_images(t_mlx *mlx)
{
    mlx_image_to_window(mlx->mlx_cnx, mlx->img, 0, 0);
    mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.gun, W_WIDTH / 2 - GUN_W / 2, W_HEIGHT - GUN_H);
    mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.fire, W_WIDTH / 2 - FIRE_W / 2, W_HEIGHT - FIRE_H);
    mlx_image_to_window(mlx->mlx_cnx, mlx->graphics.reload, W_WIDTH / 2 - RELOAD_W / 2, W_HEIGHT - RELOAD_H);
    mlx->graphics.gun->instances[0].enabled = true;
    gun_animation(mlx, 0, 0);
    mlx->graphics.reload->instances[0].enabled = false;
    mlx->graphics.fire->instances[0].enabled = false;
}

void set_hooks(t_mlx *mlx)
{
    mlx_set_mouse_pos(mlx->mlx_cnx, W_WIDTH/2, W_HEIGHT/2);
    mlx_loop_hook(mlx->mlx_cnx, keydown_handler, mlx);
    mlx_cursor_hook(mlx->mlx_cnx, mouse_handler, mlx);
    mlx_mouse_hook(mlx->mlx_cnx, fire_hook, mlx);
    mlx_set_cursor_mode(mlx->mlx_cnx, 0x00034003);
    mlx_key_hook(mlx->mlx_cnx, open_door, mlx);
    mlx_loop_hook(mlx->mlx_cnx, map_render, mlx);
    mlx_loop_hook(mlx->mlx_cnx, animation_hook, mlx);
}

int main(int ac, char **av)
{
    int i;
    t_mlx   mlx;
    t_cube  cube;
    // parsing
    if (ac < 2)
    {
        printf("need file name !\n");
        // no data leak
        return (1);
    }
    if (main_parsing(&cube, av))
        return (1);
    // end of parsing and start of leaking can t use garbage collector because it slow down the game 
  
    // EXECUTION
    bzero(&mlx, sizeof(t_mlx));
    initializer(&mlx, &cube);
    load_graphics(&mlx, &cube);

    put_images(&mlx);

    set_hooks(&mlx);
    mlx_loop(mlx.mlx_cnx);
}


