NAME = minishell

SRC = p_remain.c p_redir.c p_nodes.c p_envir.c p_dollar.c p_bigis.c \
	e_exec_cmd.c main.c b_echo.c b_cd.c b_built_ins.c b_export.c \
	b_unset.c b_export_utils.c read_loop.c e_reforked_utils.c\
	e_reforked.c s_sigaction.c p_list.c e_heredoc.c b_exit.c b_pwd.c \
	e_error_return.c e_fd_handler.c e_free_memory.c s_sigaction_utils.c\
	e_redirect.c p_checksyntax_utils.c p_checksyntax.c s_waiter.c \
	p_auxil.c p_envir_utils.c p_init_tree.c p_strings.c p_parser.c\
	p_quotes.c p_nodes_utils.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g #-lreadline -g #fsanitize=address

LIBS = -lreadline  -L/usr/local/lib

INCLUDES = -Ilibft/

LIBFT = libft/libft.a

all: $(LIBFT) $(OBJ) $(NAME)

$(LIBFT):
	@echo "\n-Compiling Libft...\n"
	@$(MAKE) -C libft

	@echo "\n-Compiling $(NAME)..."
	@echo "cc $(CFLAGS) -g $(INCLUDES) -c *.c -o *.o"

$(OBJ): %.o: %.c
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@echo "n-Linking $(NAME) with libft..."
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(LIBS)
	@make clean
	@echo "n--------------------------------"
	@echo "$(NAME) is ready!"
	@echo "-------------------------------"

clean:
	@echo "n-Cleaning Libft..."
	$(MAKE) -C libft clean
	@echo "n-Cleaning object files..."
	@rm -f $(OBJ)
	@echo "n--------------------------------"
	@echo "$(NAME) object files cleaned!"
	@echo "-------------------------------"

fclean: clean
	@echo "n-Cleaning $(NAME) and libft..."
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	@echo "n--------------------------------"
	@echo "$(NAME) object files cleaned!"
	@echo "-------------------------------"

re: fclean all

r: all
	./minishell
s: all
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
v: all
	valgrind -s --leak-check=full --show-leak-kinds=all ./minishell

# run: all
# 	./pipex infile cat "grep a" outfile

.PHONY: all clean fclean re r
