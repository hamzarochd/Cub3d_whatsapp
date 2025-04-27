CC = cc
NAME = cub3D

BNAME = cub3d_bonus

CFLAGS = -funroll-loops -O3 -ffast-math -mavx2 -flto
CFLAGS += -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g

SRC = mandatory/get_next_line.c mandatory/get_next_line_utils.c mandatory/collisions.c \
		mandatory/ft_split.c mandatory/graphics_loader.c mandatory/hooks_setter.c mandatory/initializer.c  mandatory/main.c mandatory/parsing_2.c \
		mandatory/parsing.c  mandatory/ray_calculator.c mandatory/render.c  mandatory/vertical_raycasting.c mandatory/ft_exit.c  mandatory/ft_strtrim.c \
		mandatory/general_tools.c mandatory/graphic_tools.c mandatory/horizontal_raycasting.c mandatory/keys_hook.c mandatory/parsing_1.c mandatory/parsing_3.c \
		mandatory/pixel_putters.c mandatory/raycasting_tools.c mandatory/tools.c

OBJ = $(SRC:.c=.o)

BSRC = bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c bonus/collisions_bonus.c \
		bonus/firing_bonus.c bonus/ft_strtrim_bonus.c bonus/graphics_loader_bonus.c bonus/horizontal_raycasting_bonus.c \
		bonus/main_bonus.c bonus/parsing_2_bonus.c bonus/pixel_putters_bonus.c bonus/reloading_bonus.c bonus/vertical_raycasting_bonus.c \
		bonus/ft_exit_bonus.c bonus/graphic_tools_bonus.c bonus/initializer_bonus.c bonus/minimap_bonus.c bonus/parsing_3_bonus.c \
		bonus/ray_calculator_bonus.c bonus/render_bonus.c bonus/walking_bonus.c bonus/door_handler_bonus.c bonus/ft_split_bonus.c bonus/general_tools_bonus.c \
		bonus/hooks_setter_bonus.c bonus/keys_hook_bonus.c bonus/parsing_1_bonus.c bonus/parsing_bonus.c bonus/raycasting_tools_bonus.c bonus/tools_bonus.c

BOBJ = $(BSRC:.c=.o)

INCLUDES = -Iinclude -ldl -lglfw -pthread -lm

MLX = MLX42/build/libmlx42.a

all:  $(NAME) 

bonus : $(BNAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(MLX) -o $(NAME) 

$(BNAME): $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) $(INCLUDES) $(MLX) -o $(BNAME) 

%.o: %.c mandatory/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@ 

%bonus.o: %bonus.c bonus/cub3d_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: clean
