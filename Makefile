# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 14:31:20 by rreedy            #+#    #+#              #
#    Updated: 2018/12/04 19:33:48 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a

POBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/ft_printf/*.c))
LOBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CFLAGS += -Wall -Wextra -Werror -I./includes

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(POBJS) $(LOBJS)
	ar rc $(NAME) $(POBJS) $(LOBJS)
	ranlib $(NAME)

clean:
	@- $(RM) $(LOBJS) $(POBJS)

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
