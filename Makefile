# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 23:27:31 by lmunoz-q          #+#    #+#              #
#    Updated: 2018/09/06 11:49:29 by lmunoz-q         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

CFLAGS = -Ofast -Wall -Wextra -Werror

CLIB = -L libft -lft -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

SRCFILES = main.c \

INC = inc \

DIRS =

INCDIRS = $(addprefix -I,$(INC))

OBJDIR = obj

OBJECTS = $(SRCFILES:%.c=$(OBJDIR)/%.o)

SRCDIRS := $(addprefix src/,$(DIRS))

vpath %.c src $(SRCDIRS)

all: $(NAME)

$(NAME): libft/libft.a minilibx_macos/libmlx.a $(OBJECTS)
	$(CC) $(INCDIRS) $(CLIB) -o $@ $(OBJECTS)

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) $(INCDIRS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

libft/libft.a: force
	$(MAKE) -w -C libft/
	$(MAKE) -w -C minilibx_macos/

minilibx_macos/libmlx.a: force
	$(MAKE) -w -C minilibx_macos/

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -w -C libft/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -w -C libft/ fclean

re: fclean all

force:
	true

.PHONY: all clean fclean re
