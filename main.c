#include "cub3d.h"

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
        return (ft_printf("map empty\n"), 1);
    cube->file_content = calloc(count + 1, sizeof(char *));
    close(cube->fd);
    cube->fd = open(cube->file_name, O_RDONLY);
    if (cube->fd == -1)
        return (ft_printf("fd error\n"), 1);
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
            return (ft_printf("NO texture already set\n"), 1);
        cube->no_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "SO") == 0)
    {
        if (cube->so_tex != NULL)
            return (ft_printf("SO texture already set\n"), 1);
        cube->so_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "WE") == 0)
    {
        if (cube->we_tex != NULL)
            return (ft_printf("WE texture already set\n"), 1);
        cube->we_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "EA") == 0)
    {
        if (cube->ea_tex != NULL)
            return (ft_printf("EA texture already set\n"), 1);
        cube->ea_tex = strdup(splitted[1]);
        counter++;
    }
    else if (strcmp(splitted[0], "F") == 0)
    {
        if (cube->floor_color != NULL)
            return (ft_printf("floor color already set\n"), 1);
        cube->floor_color = color_join(splitted);
        counter++;
    }
    else if (strcmp(splitted[0], "C") == 0)
    {
        if (cube->ceiling_color != NULL)
            return (ft_printf("ceiling color already set\n"), 1);
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


void init_cube(t_cube *cube)
{

    cube->no_tex = NULL;
    cube->so_tex = NULL;
    cube->we_tex = NULL;
    cube->ea_tex = NULL;
    cube->floor_color = NULL;
    cube->ceiling_color = NULL;
}

typedef struct s_player {
    double     x_player;
    double     y_player;
    double     rot_angle;
} t_player;

typedef struct s_point {
    double x;
    double y;
}               t_point;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map {
    int     width;
    int     height;
}   t_map;

typedef struct s_mlx {
    void    *mlx_cnx;
    void    *mlx_win;
    t_data  img;
    t_map   *map;
    t_cube  *cube;
    t_player    *player;
}   t_mlx;



enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


#define TILE_SIZE 128
#define ARROW_LEFT 65361
#define ARROW_UP 65362
#define ARROW_RIGHT 65363
#define ARROW_DOWN 65364
#define LEFT 97
#define UP 119
#define RIGHT 100
#define DOWN 115
#define ESC 65307
#define PI 3.141592654
#define SPEED 20.0


void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
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
        my_mlx_pixel_put(&mlx->img, pixel_pt.x, pixel_pt.y, 0xFFFFFF);
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
                my_mlx_pixel_put(&mlx->img, x, y, color);
            }
        }
    }
}

int is_in_wall(char **map, double x, double y, t_mlx *mlx)
{
    int map_x;
    int map_y;



    map_x = x / TILE_SIZE;
    map_y = y / TILE_SIZE;

    printf("mapx = %d\nmapy = %d\n", map_x, map_y);
    if (map_x < (mlx->map->width / TILE_SIZE) && map_y < (mlx->map->height / TILE_SIZE)
        && map_x >= 0 && map_y >= 0)
    {
        if(map[map_y][map_x] == '1')
            return 1;
        else
            return 0;
    }
    return 0;
}

t_point get_h_wall(t_mlx *mlx, char **map, t_point player_pt, double rot_angle)
{
    t_point wall_pt;
    double  angle;
    double  cat;
    // int     found_wall;

    wall_pt.x = 0;
    wall_pt.y = 0;
    angle = 0;
    cat = 0;
    // found_wall = 0;

    (void)mlx;
    (void)map;
    (void)player_pt;

    if (rot_angle < PI / 2)
        angle = rot_angle;
    else if (rot_angle < PI)
        angle = PI - rot_angle;
    else if (rot_angle < ((3 * PI) / 2))
        angle = rot_angle - PI;
    else
        angle = (2 * PI) - rot_angle;
    
    printf("rot_angle = %f radians --> %f degrees\nangle = %f radians --> %f degrees\n", rot_angle, (rot_angle * 180) / PI, angle, (angle * 180) / PI);

    if (rot_angle < PI)
        cat = player_pt.x - (TILE_SIZE * (int)(player_pt.x / TILE_SIZE));
    else
        cat = (TILE_SIZE * ((int)(player_pt.x / TILE_SIZE) + 1)) - player_pt.x;

    printf("x = %f\ncat = %f\n", player_pt.x, cat);

    // while (!found_wall)
    // {
        
    // }
    

    printf("is in wall = %d\n", is_in_wall(map, TILE_SIZE * 2.5, TILE_SIZE - 1, mlx));
    

    return wall_pt;
}

t_point calculate_rayend(t_mlx *mlx, char **map, t_point player_pt, double angle)
{
    t_point h_wall;
    t_point v_wall;

    h_wall.x = 0;
    h_wall.y = 0;
    v_wall.x = 0;
    v_wall.y = 0;

    h_wall = get_h_wall(mlx, map, player_pt, angle);
    return h_wall;
}

void map_render(t_mlx *mlx)
{
    int	x;
	int	y;
    int map_x;
    int map_y;
    t_point player_pt;
    t_point line_end_pt;
    double line_lenght;

    map_x = 0;
    map_y = 0;

	y = 0;
	while (y < mlx->map->height)
	{
        map_y = y / TILE_SIZE;
		x = 0;
		while (x < mlx->map->width)
		{
            map_x = x / TILE_SIZE;
            if ((x % TILE_SIZE == 0) || (y % TILE_SIZE == 0))
                my_mlx_pixel_put(&mlx->img, x, y, 0x000000);
            else if (mlx->cube->map[map_y][map_x] == '0')
            {
                // if(x > mlx->player->x_player - 5 && x < mlx->player->x_player + 5
                //     && y > mlx->player->y_player - 5 && y < mlx->player->y_player + 5)
                //     my_mlx_pixel_put(&mlx->img, x, y, 0x00FF00);
                // else
                    my_mlx_pixel_put(&mlx->img, x, y, 0x0000FF);
            }
			    
            else if(mlx->cube->map[map_y][map_x] == 'N' || mlx->cube->map[map_y][map_x] == 'S' || mlx->cube->map[map_y][map_x] == 'E' || mlx->cube->map[map_y][map_x] == 'W')
            {
                // if(x == mlx->player->x_player && y == mlx->player->y_player)
                //     draw_filled_circle(mlx, mlx->player->x_player, mlx->player->y_player, 20, 0x00FF00);
                // else
                    my_mlx_pixel_put(&mlx->img, x, y, 0x0000FF);
    
            }
            else if (mlx->cube->map[map_y][map_x] == ' ')
            {
                my_mlx_pixel_put(&mlx->img, x, y, 0x000000);
            }
            else
            {
                my_mlx_pixel_put(&mlx->img, x, y, 0xFF0000);
            }
            // printf("%d\n", x);
            x++;
        }
        y++;
	}

    
    draw_filled_circle(mlx, mlx->player->x_player, mlx->player->y_player, 5, 0x00FF00);

    player_pt.x = mlx->player->x_player;
    player_pt.y = mlx->player->y_player;

    line_lenght = 200.0;

    // line_end_pt.x = player_pt.x + (cos(mlx->player->rot_angle) * line_lenght);
    // line_end_pt.y = player_pt.y - (sin(mlx->player->rot_angle) * line_lenght);

    // printf("angle = %f\n", mlx->player->rot_angle);
    // printf("cos = %f\n", cos(mlx->player->rot_angle));
    // printf("sin = %f\n", sin(mlx->player->rot_angle));
    // printf("from (%f, %f) to (%f, %f)\n", player_pt.x, player_pt.y, line_end_pt.x, line_end_pt.y);

    double angle_start = mlx->player->rot_angle - ((PI/180) * 33);
    // int i = 0;
    // while (i < 66)
    // {
        
        // line_end_pt.x = player_pt.x + (cos(angle_start) * line_lenght);
        // line_end_pt.y = player_pt.y - (sin(angle_start) * line_lenght);
        line_end_pt = calculate_rayend(mlx, mlx->cube->map, player_pt, angle_start);
        draw_line(mlx, player_pt, line_end_pt);
    //     angle_start += (PI / 180);
    //     i++;
    // }
    
    // draw_line(mlx, player_pt, line_end_pt);

    // printf("mapx = %d\nmapy = %d\n", map_x, map_y);
	mlx_put_image_to_window(mlx->mlx_cnx, mlx->mlx_win, mlx->img.img, 0, 0);
}



int check_wall(t_mlx *mlx, char direction)
{
    double x;
    double y;

    x = mlx->player->x_player;
    y = mlx->player->y_player;

    if (direction == 'U') 
    {
        x += cos(mlx->player->rot_angle) * SPEED;
        y -= sin(mlx->player->rot_angle) * SPEED;
    }
    else if (direction == 'D')
    {
        x -= cos(mlx->player->rot_angle) * SPEED;
        y += sin(mlx->player->rot_angle) * SPEED;
    }
    else if (direction == 'L') 
    {
        x += cos(mlx->player->rot_angle + PI / 2) * SPEED;
        y -= sin(mlx->player->rot_angle + PI / 2) * SPEED;
    }
    else if (direction == 'R') 
    {
        x += cos(mlx->player->rot_angle - PI / 2) * SPEED;
        y -= sin(mlx->player->rot_angle - PI / 2) * SPEED;
    }
    if(is_in_wall(mlx->cube->map, x, y, mlx))
        return 1;
    return 0;
}

void    move_player(t_mlx *mlx, char direction)
{
    if (check_wall(mlx, direction))
        return ;
    if (direction == 'U') 
    {
        mlx->player->x_player += cos(mlx->player->rot_angle) * SPEED;
        mlx->player->y_player -= sin(mlx->player->rot_angle) * SPEED;
    }
    else if (direction == 'D')
    {
        mlx->player->x_player -= cos(mlx->player->rot_angle) * SPEED;
        mlx->player->y_player += sin(mlx->player->rot_angle) * SPEED;
    }
    else if (direction == 'L') 
    {
        mlx->player->x_player += cos(mlx->player->rot_angle + PI / 2) * SPEED;
        mlx->player->y_player -= sin(mlx->player->rot_angle + PI / 2) * SPEED;
    }
    else if (direction == 'R') 
    {
        mlx->player->x_player += cos(mlx->player->rot_angle - PI / 2) * SPEED;
        mlx->player->y_player -= sin(mlx->player->rot_angle - PI / 2) * SPEED;
    }
}

int	destroy_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_cnx, mlx->img.img);
	mlx_destroy_window(mlx->mlx_cnx, mlx->mlx_win);
	exit(0);
	return (0);
}

int	keydown_handler(int keycode, t_mlx *mlx)
{
    (void)mlx;
    // printf("KEY PRESSED keycode = %d\n", keycode);
    if (keycode == ESC)
        destroy_handler(mlx);
    else if (keycode == LEFT)
        move_player(mlx, 'L');
    else if (keycode == UP)
        move_player(mlx, 'U');
    else if (keycode == RIGHT)
        move_player(mlx, 'R');
    else if (keycode == DOWN)
        move_player(mlx, 'D');
    else if (keycode == ARROW_LEFT)
    {
        mlx->player->rot_angle += PI / 18;
        if (mlx->player->rot_angle >= 2*PI)
            mlx->player->rot_angle -= 2*PI;
        else if (mlx->player->rot_angle < 0)
            mlx->player->rot_angle += 2*PI;
    }
    else if (keycode == ARROW_RIGHT)
    {
        mlx->player->rot_angle -= PI / 18;
        if (mlx->player->rot_angle >= 2*PI)
            mlx->player->rot_angle -= 2*PI;
        else if (mlx->player->rot_angle < 0)
            mlx->player->rot_angle += 2*PI;
    }
    map_render(mlx);
	return (0);
}

int	close_win(int keycode, t_mlx *mlx)
{
    int k = keycode;

    k = 0;
    // printf("keycode =%d\n", keycode);
	mlx_destroy_window(mlx->mlx_cnx, mlx->mlx_win);
	return (0);
}


void player_init(t_mlx *mlx, t_cube cube)
{
    int i;
    int j;
    int player_x;
    int player_y;


    i = 0;
    j = 0;
    player_x = 0;
    player_y = 0;

    if (!mlx || !mlx->player || !mlx->map || !cube.map)
    return;

    while(cube.map[i])
    {
        j = 0;
        while (cube.map[i][j])
        {
            if(cube.map[i][j] == 'N' || cube.map[i][j] == 'S' || cube.map[i][j] == 'E' || cube.map[i][j] == 'W')
            {
                player_x = j;
                player_y = i;
            }
            j++;
        }        
        i++;
    }
    mlx->player->x_player = (TILE_SIZE * player_x) + (TILE_SIZE / 2);
    mlx->player->y_player = (TILE_SIZE * player_y) + (TILE_SIZE / 2);
    // mlx->player->x_player = player_x + 0.5;
    // mlx->player->y_player = player_y + 0.5;
}

int main(int ac, char **av)
{
    t_cube  cube;
    (void)ac;
    init_cube(&cube);
    cube.file_name = ft_strdup(av[1]);
    if (check_map_name(cube.file_name) == 1)
    {
        ft_printf("map name error\n");
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
        ft_printf("[%s]\n", cube.map[i]);
        if(ft_strlen(cube.map[i]) > width_tiles)
            width_tiles = ft_strlen(cube.map[i]);
        i++;
    }
    height_tiles = i;
    

    // EXECUTION


    t_mlx   *mlx;
    int     width;
    int     height;

    mlx = malloc(sizeof(t_mlx));
    if (!mlx)
    {
        fprintf(stderr, "MALLOC ERROR\n");
        exit(1);
    }
    width = width_tiles * TILE_SIZE;
    height = height_tiles * TILE_SIZE;
    // printf("width %d\nheight %d\n", width, height);

    mlx->mlx_cnx = mlx_init();
    
    mlx->mlx_win = mlx_new_window(mlx->mlx_cnx, width, height, "CUB3D");
    mlx->img.img = mlx_new_image(mlx->mlx_cnx, width, height);
    mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);

    mlx->map = malloc(sizeof(t_map));
    if (!mlx->map)
    {
        fprintf(stderr, "MALLOC ERROR\n");
        exit(1);
    }

    mlx->cube = malloc(sizeof(t_cube));
    if (!mlx->cube)
    {
        fprintf(stderr, "MALLOC ERROR\n");
        exit(1);
    }
    mlx->cube = &cube;
    mlx->map->height = height;
    mlx->map->width = width;
    mlx->player = malloc(sizeof(t_player));
    if (!mlx->player)
    {
        fprintf(stderr, "MALLOC ERROR\n");
        exit(1);
    }
    mlx->player->x_player = 0;
    mlx->player->y_player = 0;
    mlx->player->rot_angle = PI / 2;



    player_init(mlx, cube);

    // printf("player x = %f\nplayer y = %f\n", mlx->player->x_player, mlx->player->y_player);

    map_render(mlx);
    // mlx_hook(mlx->mlx_win, 2, 1L<<0, close_win, &mlx);
    mlx_hook(mlx->mlx_win, 2, (1L<<0), keydown_handler, mlx);
    mlx_hook(mlx->mlx_win, 17, 1L<<0, destroy_handler, &mlx);
    mlx_loop(mlx->mlx_cnx);


}