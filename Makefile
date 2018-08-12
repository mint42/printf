# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mint </var/spool/mail/mint>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/10 16:37:25 by mint              #+#    #+#              #
#    Updated: 2018/08/10 16:46:38 by mint             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

b_NAME := printf
NAME := libftprintf.a;
CFLAGS := -Wall -Wextra -Werror 
SRCS := $(wildcard *.c)

OBJS := $(SRCS .c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	@- $(RM) $(OBJS)

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
