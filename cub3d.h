#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include "printf/ft_printf.h"
// # include <mlx.h>
# include <math.h>
# include <strings.h>

#include <fcntl.h>
#include "./MLX42/include/MLX42/MLX42.h"
#include <sys/time.h>

#define W_HEIGHT 1280
#define W_WIDTH 2560

#define TILE_SIZE 1280
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
#define SPEED 200
#define MINIMAP_SCALE 20
#define MAX_DISTANCE 15 * TILE_SIZE
# define GUN_W 877
# define GUN_H 580
# define FIRE_W 898
# define FIRE_H 570
# define RELOAD_W 1394
# define RELOAD_H 736
# define MAP_RADIUS 128
# define MAP_X 192
# define MAP_Y 192

typedef struct  s_cube
{
	char    *file_name;
	char    *no_tex;
	char    *so_tex;
	char    *we_tex;
	char    *ea_tex;
	int    	floor_color[3];
	int    	ceiling_color[3];
	char    **file_content;
	char    **map;
	char    player_direction;
	int     fd;
	int     player_x;
	int     player_y;
}               t_cube;

typedef struct  s_player {
	double     x_player;
	double     y_player;
	double     rot_angle;
}               t_player;

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

typedef struct  s_map {
	int     width;
	int     height;
}               t_map;

typedef struct  s_ray
{
	double  ray_length;
	double	ray_pixels;
	char    wall_orientation;
	int     tile_hit_point;
	int     is_door;
	double	delta_angle;
}               t_ray;

typedef struct	s_minimap
{
	double	scale;
    double	rot_angle;
    double	cos_angle;
    double	sin_angle;
    int		map_pixel_width;
    int		map_pixel_height;
	int		tile_x;
	int		tile_y;
	t_point	tip;
	int		x;
	int		y;
	int		dx;
	int		dy;
}				t_minimap;

typedef struct	s_tex
{
	uint32_t	texel_x;
	uint32_t	texel_y;
	uint32_t	texel_color;
	double		tex_index;
}				t_tex;

typedef struct 	s_render_indexes
{
	int		i;
	int 	j;
	double	angle_start;
}				t_rendex;


typedef struct s_wall
{
	int			wall_start;
	int			wall_end;
	double		wall_prop;
	mlx_image_t *wall_texture;
	t_tex		tex;
	t_ray		*ray;
}				t_wall;

typedef struct  s_graphics
{
	mlx_image_t *no_txtr;
	mlx_image_t *so_txtr;
	mlx_image_t *ea_txtr;
	mlx_image_t *we_txtr;
	mlx_image_t *door_txtr;
	mlx_image_t *sky_image;
	mlx_image_t *gun;
	mlx_image_t *reload;
	mlx_image_t *player;
	mlx_image_t *fire;
	mlx_image_t *north;
	mlx_texture_t *fire_tex;
	mlx_texture_t *reload_tex;
	mlx_texture_t *gun_tex;
}               t_graphics;

typedef struct  s_mlx {
	mlx_t    *mlx_cnx;
	void    *mlx_win;
	mlx_image_t *img;
	t_map   map;
	t_cube  *cube;
	t_graphics graphics;
	t_player    player;
	int         minimap_scale;
	int         is_walking;
	int         is_firing;
	int         is_reloading;
	int         is_holding;
	double		wall_const;
}               t_mlx;



enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};





char	*get_next_line(int fd);
char	*ft_line(char **str);
char	*ft_read(char *str);
int 	ft_strlen( char *str);
char	*my_free(char *s1, char **s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char const *set);
char    *color_join(char    **splitted);
int 	check_config(t_cube *cube);
char    **refill_map(t_cube *cube);
void	init_cube(t_cube *cube);
int		check_map_name(char *str);
int		read_file(t_cube *cube);
int		parse_file(t_cube *cube);
void	ft_exit(t_mlx *mlx);
int		check_map(t_cube *cube);
int		main_parsing(t_cube *cube, char **av);
char	*ft_strtrim_last(char *s1, char const *set);
void	free_double(char **ptr);
int		is_invalid_rgb(char *input, t_cube *cube, char *tag);


#endif