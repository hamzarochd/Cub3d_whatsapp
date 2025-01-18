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

#include <fcntl.h>

typedef struct s_cube
{
    char    *file_name;
    char    *no_tex;
    char    *so_tex;
    char    *we_tex;
    char    *ea_tex;
    char     *floor_color;
    char     *ceiling_color;
    char    **file_content;
    char    **map;
    char    player_direction;
    int     fd;
    int     player_x;
    int     player_y;
} t_cube;

char	*get_next_line(int fd);
char	*ft_line(char **str);
char	*ft_read(char *str);
int 	ft_strlen( char *str);
char	*my_free(char *s1, char **s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char const *s1, char const *set);
#endif