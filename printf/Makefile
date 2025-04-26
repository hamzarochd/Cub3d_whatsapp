NAME = libftprintf.a

SRCS = ft_put_c.c ft_printf.c ft_put_s.c ft_exec.c ft_put_x.c ft_put_p.c \
		 ft_put_u.c ft_put_d.c 
	   

OBJS = $(SRCS:.c=.o)

CC = cc

HEADER = ft_printf.h

CFLAGS = -Wall -Wextra -Werror

rm = rm -f

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) 
		 ar rcs $(NAME) $(OBJS)

clean :
	$(rm) $(OBJS)

fclean : clean
	$(rm) $(NAME)

re : fclean all

.PHONY : all clean fclean re