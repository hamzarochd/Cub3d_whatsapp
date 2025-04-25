CC = cc
# CFLAGS = -O3 -mavx2 -flto 
CFLAGS = -funroll-loops -O3 -ffast-math -mavx2 -flto
# CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address -g

SRC = getnext/get_next_line.c getnext/get_next_line_utils.c main.c ft_strtrim.c ft_split.c parsing.c tools.c parsing_1.c parsing_2.c parsing_3.c initializer.c \
		graphics_loader.c ft_exit.c walking.c reloading.c firing.c keys_hook.c door_handler.c collisions.c render.c minimap.c ray_calculator.c vertical_raycasting.c \
		horizontal_raycasting.c
OBJ = $(SRC:.c=.o)
NAME = cub3d
PRINTF = printf/libftprintf.a

INCLUDES = -Iinclude -ldl -lglfw -pthread -lm 
MLX = MLX42/build/libmlx42.a

all:  $(NAME) 

$(NAME): $(OBJ)
	$(CC)   $(CFLAGS) $(OBJ) $(PRINTF) $(INCLUDES) $(MLX) -o $(NAME) 

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: clean


# -fsanitize=address -g