# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 23:27:31 by lmunoz-q          #+#    #+#              #
#    Updated: 2018/09/15 20:49:24 by lmunoz-q         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc

CFLAGS = -Ofast -Wall -Wextra -Werror

CLIB = -L libft -lft -L glfw-3.2.1/src -lglfw3 -L glfw-3.2.1/glad -lglad -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

SRCFILES = main.c \
		   default_map.c \
		   load_map.c \
		   save_map.c \

INC = inc \
	  glfw-3.2.1/include \
	  glfw-3.2.1/glad/include

DIRS = parsing

INCDIRS = $(addprefix -I,$(INC))

OBJDIR = obj

OBJECTS = $(SRCFILES:%.c=$(OBJDIR)/%.o)

SRCDIRS := $(addprefix src/,$(DIRS))

GLFWLIB := glfw-3.2.1/src/libglfw3.a

GLADLIB := glfw-3.2.1/glad/glad.a

vpath %.c src $(SRCDIRS)

all: $(NAME)

$(NAME): libft/libft.a $(GLFWLIB) $(GLADLIB) $(OBJECTS)
	$(CC) $(INCDIRS) $(CLIB) -o $@ $(OBJECTS)

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) $(INCDIRS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

libft/libft.a:
	$(MAKE) -w -C libft/

$(GLFWLIB):
	cd glfw-3.2.1; \
	cmake CMakeLists.txt; \
	make; \
	cd ..

$(GLADLIB):
	cd glfw-3.2.1/glad/; \
	make; \
	cd ../..

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -w -C libft/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -w -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
