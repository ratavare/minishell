NAME		=		minishell

# $(VERBOSE).SILENT:

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -g

INCLUDES	=		-I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

LIBFT		=		./libft/libft.a

FT_PRINTF		=		./libft/ft_printf/libftprintf.a

GNL			=		./libft/get_next_line/*.c

RM			=		rm -f

SRC 		=		srcs/*.c srcs/executor/*.c srcs/lexer/*.c srcs/parser/*.c ./libft/ft_printf/srcs/*.c srcs/builtins/*.c

all:		$(NAME)

$(NAME):	$(LIBFT) $(SRC)
			$(CC) $(CFLAGS) $(SRC) $(GNL) $(LIBFT) $(INCLUDES) -lreadline -o $(NAME)
		
$(LIBFT):
			make -C ./libft

clean:		
			make clean -C ./libft
			$(RM) $(NAME)
fclean:
			make fclean -C ./libft
			$(RM) $(NAME)

re:		fclean	$(NAME)

v:
			make && valgrind --leak-check=full --show-leak-kinds=all --suppressions=".minishell.sup" ./minishell
			