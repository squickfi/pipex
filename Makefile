NAME = pipex

# SRCS = check_input.c\
# 		ft_split.c\
# 		ft_strjoin.c\
# 		funcs_for_pipe_fds.c\
# 		get_exec_arguments.c\
# 		get_next_line_utils.c\
# 		gnl/get_next_line.c\
# 		handle_here_doc.c\
# 		handle_multipipes.c\
# 		libft_funcs.c\
# 		libft_funcs2.c\
# 		parse_cmd_args.c\
# 		parse_cmd_args2.c\
# 		non_bonus_pipex.c

SRCS = $(addprefix srcs/,\
		check_input.c\
		ft_split.c\
		ft_strjoin.c\
		funcs_for_pipe_fds.c\
		get_exec_arguments.c\
		get_next_line_utils.c\
		get_next_line.c\
		handle_here_doc.c\
		handle_multipipes.c\
		libft_funcs.c\
		libft_funcs2.c\
		parse_cmd_args.c\
		parse_cmd_args2.c\
		pipex.c)

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -I includes/

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(DEPS)
	
fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all