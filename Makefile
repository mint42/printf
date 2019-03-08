# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 14:31:20 by rreedy            #+#    #+#              #
#    Updated: 2019/03/08 15:10:53 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

CC := gcc
POBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/ft_printf/*.c))
LOBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CFLAGS += -Wall -Wextra -Werror -I./includes
LFLAGS += -L./ -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(POBJS) $(LOBJS)
	ar rc $(NAME) $(POBJS) $(LOBJS)
	ranlib $(NAME)

test: all main.o
	$(CC) $(CFLAGS) tester.o $(LFLAGS)

clean:
	@- $(RM) $(LOBJS) $(POBJS) a.out tester.o

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
