# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jandre <jandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/06 19:35:19 by jandre            #+#    #+#              #
#    Updated: 2021/06/07 16:47:14 by jandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = sources/
SRCS = ft_error.c ft_get_path.c ft_pipex.c ft_split.c ft_strjoin.c \
	ft_strlen.c ft_strncmp.c ft_substr.c ft_strdup.c
SRC =  $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf pipex

re: fclean
	make all