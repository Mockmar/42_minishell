CC		= cc -O3
CFLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -L$(LIBFT_DIR)
LINKS	= -lft -lm -lreadline

### EXECUTABLE ###
NAME	= minishell

### INCLUDES ###
OBJ_DIR		= bin
SRC_DIR		= srcs
HEADER		= incl
LIBFT_DIR	= Libft
LIBFT		= $(LIBFT_DIR)/libft.a

### SOURCE FILES ###
SRCS	= 	main.c \
			token-izer.c \
			tok_lst.c \
			lexer.c \
			ft_split_cmd.c \
			dollar.c \
			launch_minishell.c \
			init_token.c \
			bin_path.c \
			parsing.c \
			gestion_error.c \
			heredoc.c \
			trim_cmd.c \
			bultins.c \
			my_exit.c \
			my_echo.c \
			env.c \
			env_lst.c \
			my_env.c \
			my_cd.c \
			my_export.c \
			my_export2.c \
			my_pwd.c \
			my_unset.c \
			big_free.c \
			redir1.c \
			redir2.c \
			rm_quote.c \
			shell_print.c \
			exec_fork.c \
			exec_redir.c \
			execution.c \
			pipex.c \
			syntax_check.c \
			chev_err.c \
			sig_in.c \


### OBJECTS ###
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

### COLORS ###
NOC		= \033[0m
BLACK	= \033[1;30m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m

### RULES ###
all:	$(NAME)

$(LIBFT):
	@echo "$(GREEN)Creating libft lib file$(NOC)"
	@make bonus -C $(LIBFT_DIR)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(LINKS) -o $(NAME)
	@echo "$(GREEN)Project successfully compiled$(NOC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER)/$(NAME).h
	@$(CC) $(CFLAGS) -I$(HEADER) -I$(LIBFT_DIR)/$(HEADER) -c $< -o $@
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(GREEN)[Done]$(NOC)"

run: $(NAME)
	@./minishell

val: $(NAME)
	@valgrind --track-origins=yes --leak-check=full ./minishell

clean:
	@echo "$(GREEN)Supressing libraries files$(NOC)"
	@make clean -C $(LIBFT_DIR)
	@echo "$(GREEN)Supressing object files$(NOC)"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@make fclean -C $(LIBFT_DIR)
	@echo "$(GREEN)Supressing program file$(NOC)"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
