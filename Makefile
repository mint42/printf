# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mint </var/spool/mail/mint>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/10 16:37:25 by mint              #+#    #+#              #
#    Updated: 2018/08/30 15:22:54 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./*.c))
LOBJS := $(patsubst %.c,%.o,$(wildcard ./libft/*.c))

CFLAGS += -Wall -Wextra -Werror -I./includes -I./libft/includes
LFLAGS += -L./ -lftprintf

.PHONY: all clean fclean binary rmbinary re

all: $(NAME)

$(NAME): $(OBJS) $(LOBJS)
	ar rc $(NAME) $(OBJS) $(LOBJS)
	ranlib $(NAME)

binary: $(NAME)
	$(CC) $(CFLAGS) ~/cadet/test_main/ft_printf_main.c $(LFLAGS) -o binary

rmbinary:
	@- $(RM) binary

clean:
	@- $(RM) $(OBJS) $(LOBJS)

fclean: clean rmbinary
	@- $(RM) $(NAME) libft/libft.a

re: fclean all
