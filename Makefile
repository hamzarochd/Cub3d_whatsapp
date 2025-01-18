CC = cc
CFLAGS = 
SRC = getnext/get_next_line.c getnext/get_next_line_utils.c main.c ft_strtrim.c ft_split.c 
OBJ = $(SRC:.c=.o)
NAME = cub3d
PRINTF = printf/libftprintf.a

all:  $(NAME) 

$(NAME): $(OBJ)
	$(CC) -g $(OBJ) $(PRINTF) -o $(NAME) 

%.o: %.c cub3d.h
	$(CC)  -g $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: clean
