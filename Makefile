# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlyessa <jlyessa@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 21:04:29 by jlyessa           #+#    #+#              #
#    Updated: 2021/03/14 10:10:27 by jlyessa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g
LIBS = -L libft -lft
INCLDS = -I libft/ -I includes/

SRCS = 	srcs/main.c \
		srcs/env/parser_env.c \
		srcs/env/util_env.c \
		srcs/parser/parser_string.c \
		srcs/parser/parser_shielding.c \
		srcs/parser/parser_variables.c \
		srcs/parser/parser_quotes.c \
		srcs/parser/parser_cmd.c \
		srcs/parser/parser_path.c \
		srcs/parser/parser_syntax.c \
		srcs/parser/utils.c \
		srcs/parser/utils_spec.c \
		srcs/parser/convert.c \
		srcs/init/init.c \
		srcs/clear/clear.c \
		srcs/clear/error.c \
		srcs/cmd/ft_echo.c \
		srcs/cmd/ft_pwd.c \
		srcs/cmd/ft_export.c \
		srcs/cmd/ft_env.c \
		srcs/cmd/ft_unset.c \
		srcs/cmd/ft_cd.c \
		srcs/cmd/ft_exit.c \
		srcs/pipe/redirection.c \
		srcs/pipe/run_pipe.c \
		srcs/parser/cmd_wrapper.c \
		srcs/signals/signals.c \
		srcs/parser/parser_redir.c \
		srcs/pipe/utils.c \
		srcs/strs/strs_size.c \
		srcs/env/remove_env.c \
		srcs/pipe/child_proc.c

OBJ = $(SRCS:.c=.o)

HEADER = includes/minishell.h libft/libft.h

%.o: %.c $(HEADER)
	@echo $<
	@gcc $(FLAGS) -c -o $@ $< $(INCLDS)

all: $(NAME)

$(NAME): $(OBJ)
	@echo 'libft/libft.a'
	@make -C libft > /dev/null
	@echo 'minishell'
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBS) $(INCLDS)
	@echo 'Done'

bonus: all

clean:
	rm -f $(OBJ)
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

norminette:
	@norminette $(SRCS) $(HEADER) libft/*.c

.PHONY: all clean fclean bonus re norminette