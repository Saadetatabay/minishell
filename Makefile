NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I.
SRC = main.c \
      lexer/lexer.c \
	  lexer/utils_token.c \
	  expander/expander.c \
	  parser/parser.c \
	  parser/parser_utils.c \
	  env/env.c \
	  executor/get_path.c \
	  executor/exec_utils.c \
	  executor/executor.c \
	  builtin/builtin1.c \
	  builtin/builtin_utils.c \
	  builtin/export.c \
	  builtin/unset.c \
	  builtin/cd.c \
	  builtin/echo.c \
	  redirections/redir.c \
	  utils.c
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