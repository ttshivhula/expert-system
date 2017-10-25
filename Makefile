# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/17 10:29:57 by ttshivhu          #+#    #+#              #
#    Updated: 2017/10/17 10:29:58 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = expert_system

SRC = main.c reader.c solver.c get_next_line.c list.c algorithm.c \

FLAG = -g3 -Wall -Werror -Wextra

SILENT = --no-print-directory

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME):
	@make -C libft $(SILENT)
	@gcc $(FLAG) -c $(SRC)
	@gcc $(FLAG) $(OBJ)  libft/libft.a -lreadline -o $(NAME)
	@printf "\x1b[32mCompiling the AI 👽\x1b[0m\n"
	@sleep 5
	@printf "\x1b[32mCompiled $(NAME) 👍\x1b[0m\n"

clean:
	@make clean -C libft $(SILENT)
	@/bin/rm -f $(OBJ) $(LOBJ) *.o
	@printf "\x1b[31mRemoved object files\x1b[0m\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft $(SILENT)
	@printf "\x1b[31mRemoved $(NAME)\x1b[0m\n"

re: fclean all
