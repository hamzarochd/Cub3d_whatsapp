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
// # include <mlx.h>
# include <math.h>
# include <strings.h>

# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <sys/time.h>

# define W_HEIGHT 1280
# define W_WIDTH 2560
# define TILE_SIZE 1280
# define PI 3.141592654
# define SPEED 200
# define MAX_DISTANCE 15 * TILE_SIZE

typedef struct s_cube
{
	char	*file_name;
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**file_content;
	char	**map;
	char	player_direction;
	int		fd;
	int		player_x;
	int		player_y;
}	t_cube;

typedef struct s_player
{
	double	x_player;
	double	y_player;
	double	rot_angle;
}	t_player;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	int	width;
	int	height;
}	t_map;

typedef struct s_ray
{
	double	ray_length;
	double	ray_pixels;
	char	wall_orientation;
	int		tile_hit_point;
	double	delta_angle;
}	t_ray;

typedef struct s_tex
{
	uint32_t	texel_x;
	uint32_t	texel_y;
	uint32_t	texel_color;
	double		tex_index;
}	t_tex;

typedef struct s_render_indexes
{
	int		i;
	int		j;
	double	angle_start;
}	t_rendex;

typedef struct s_wall
{
	int			wall_start;
	int			wall_end;
	double		wall_prop;
	mlx_image_t	*wall_texture;
	t_tex		tex;
	t_ray		*ray;
}	t_wall;

typedef struct s_graphics
{
	mlx_image_t	*no_txtr;
	mlx_image_t	*so_txtr;
	mlx_image_t	*ea_txtr;
	mlx_image_t	*we_txtr;
	mlx_image_t	*loading_img;
}	t_graphics;

typedef struct s_mlx
{
	mlx_t		*mlx_cnx;
	void		*mlx_win;
	mlx_image_t	*img;
	t_map		map;
	t_cube		*cube;
	t_graphics	graphics;
	t_player	player;
	int			is_loading;
	double		wall_const;
	double		time;
}	t_mlx;

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void		*salloc(int s);
int			destroy_handler(void);
char		*ft_read(char *str);
void		ft_exit(t_mlx *mlx);
char		*ft_line(char **str);
char		*ft_strdup(char *s1);
int			ft_strlen( char *str);
void		render(void *param);
void		set_hooks(t_mlx *mlx);
char		*get_next_line(int fd);
void		free_all(t_cube *cube);
void		put_images(t_mlx *mlx);
void		init_cube(t_cube *cube);
int			check_map(t_cube *cube);
int			read_file(t_cube *cube);
void		free_double(char **ptr);
void		init_cube(t_cube *cube);
int			parse_file(t_cube *cube);
int			check_map_name(char *str);
char		**refill_map(t_cube *cube);
int			check_config(t_cube *cube);
void		free_textures(t_cube *cube);
void		keydown_handler(void *param);
char		*my_free(char *s1, char **s2);
void		normalize_angle(double *angle);
uint32_t	rgb(int r, int g, int b, int a);
char		*ft_strjoin(char *s1, char *s2);
t_point		infinite_ray(double *ray_lenght);
char		**ft_split(const char *s, char c);
char		*ft_strchr(const char *str, int c);
void		put_floor(t_mlx *mlx, int i, int *j);
int			main_parsing(t_cube *cube, char **av);
void		initializer(t_mlx *mlx, t_cube *cube);
int			check_wall(t_mlx *mlx, char direction);
char		*ft_strtrim(char *s1, char const *set);
void		load_graphics(t_mlx *mlx, t_cube *cube);
char		*ft_strtrim_last(char *s1, char const *set);
mlx_image_t	*textures_loader(t_mlx *mlx, const char *path);
int			clamp_value(int value, int min_val, int max_val);
void		put_wall(t_mlx *mlx, int i, int *j, t_wall wall);
int			is_invalid_rgb(char *input, t_cube *cube, char *tag);
void		put_ceiling(t_mlx *mlx, int i, int *j, int wall_start);
int			is_in_wall(char **map, double x, double y, t_mlx *mlx);
int			check_color(t_cube *cube, char **splitted, char *line);
int			check_texture(t_cube *cube, char **splitted, char *line);
char		get_wall_orientation(double angle, int is_wall_horizontal);
void		vec_init(t_point *unit_vec, double ray_angle, int *found_wall);
t_ray		calculate_ray_lenght(t_mlx *mlx, t_point player_pt, double angle);
int			handle_config(t_cube *cube, char **splitted, char *line,
				int counter);
t_point		get_h_wall(t_mlx *mlx, t_point player_pt, double ray_angle,
				double *ray_lenght);
t_point		get_v_wall(t_mlx *mlx, t_point player_pt, double ray_angle,
				double *ray_lenght);

#endif