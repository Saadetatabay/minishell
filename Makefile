NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft
SRC = main.c lexer.c utils_token.c env.c utils.c expander.c parser_utils.c
OBJ = $(SRC:.c=.o)

LIBFT_PATH = ./libft
LIBFT      = $(LIBFT_PATH)/libft.a
LDFLAGS = -L$(LIBFT_PATH) -lft -lreadline

all:$(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re : fclean all

.PHONY: all clean fclean re