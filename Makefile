CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -O3
SRC = getnext/get_next_line.c getnext/get_next_line_utils.c main.c ft_strtrim.c ft_split.c 
OBJ = $(SRC:.c=.o)
NAME = cub3d
PRINTF = printf/libftprintf.a

all:  $(NAME) 

$(NAME): $(OBJ)
	$(CC)   $(CFLAGS) $(OBJ) $(PRINTF) -lmlx -lXext -lX11 -lm -lbsd -o $(NAME) 

%.o: %.c cub3d.h
	$(CC)  -g $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: clean


# -fsanitize=address -g