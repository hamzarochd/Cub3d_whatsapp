CC = cc
# CFLAGS = -O3 -mavx2 -flto 
CFLAGS = -funroll-loops -O3 -ffast-math -mavx2 -flto 
# CFLAGS =  -fsanitize=address -g

SRC = getnext/get_next_line.c getnext/get_next_line_utils.c main.c ft_strtrim.c ft_split.c 
OBJ = $(SRC:.c=.o)
NAME = cub3d

INCLUDES = -Iinclude -ldl -lglfw -pthread -lm 
MLX = MLX42/build/libmlx42.a

all:  $(NAME) 

$(NAME): $(OBJ)
	$(CC)   $(CFLAGS) $(OBJ)  $(INCLUDES) $(MLX) -o $(NAME)
%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: clean


# -fsanitize=address -g