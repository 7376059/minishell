# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgrady <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 23:32:40 by dgrady            #+#    #+#              #
#    Updated: 2019/04/29 18:15:47 by dgrady           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
SRC_NAME = cd.c flexer.c ft_delete_tilda.c main.c seteetnv_env.c  unsetenv_echo.c \
		   executor.c  ft_delete_dollar.c parser.c stuff.c 

NAME = minishell

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

all :$(NAME)

$(NAME):
	@make re -C ./libft
	@gcc $(FLAGS) -I includes/ -c $(SRC)
	@gcc $(FLAGS) -I includes/ $(OBJ) -o $(NAME) ./libft/libft.a

clean:
	@make clean -C ./libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all
