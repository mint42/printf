# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mint </var/spool/mail/mint>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/10 16:37:25 by mint              #+#    #+#              #
#    Updated: 2018/08/12 16:39:14 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf
LNAME := libft

OBJS := $(patsubst %.c,%.o,$(wildcard ./*.c))
LOBJS := $(patsubst %.c,%.o,$(wildcard ./$(LNAME)/*.c))

CFLAGS += -Wall -Wextra -Werror -I./includes -I./libft/includes
LFLAGS += -L./$(LNAME) -lft

.PHONY: all $(LNAME) clean fclean re

all: $(NAME)

$(NAME): $(LNAME) $(OBJS)
	ar rc $(NAME).a $(OBJS)
	ranlib $(NAME).a

$(LNAME): $(LOBJS)
	ar rc $(LNAME)/$(LNAME).a $(LOBJS)
	ranlib $(LNAME)/$(LNAME).a

binary: $(NAME)
	$(CC) $(CFLAGS) -I./includes $(OBJS) $(LFLAGS) -o $(NAME)

rmbinary:
	@- $(RM) libftprintf

clean:
	@- $(RM) $(OBJS) $(LOBJS)

fclean: clean rmbinary
	@- $(RM) $(NAME).a $(LNAME)/$(LNAME).a

re: rmbinary fclean all
