NAME = wolf3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

CLIB = -L libft -lft -L glfw-3.2.1/src -lglfw3 -L glfw-3.2.1/glad -lglad -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -L glfw-3.2.1/freetype-2.9.1/objs/.libs -lfreetype glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib

SRCFILES = main.c \
		   glfw_init.c \
		   new_window.c \
		   refresh_window.c \
		   env.c \
		   map_editor.c \
		   default_map.c \
		   glfw_remove_window.c \
		   draw_map.c \
		   load_map.c \
		   save_map.c \
		   rotate_2d.c \
		   line.c \
		   color_blend.c \
		   pixel.c \
		   square.c \
		   init.c \
		   text.c \
		   get_pixel.c \
		   char.c

INC = inc \
	  glfw-3.2.1/include \
	  glfw-3.2.1/glad/include \
	  libft \
	  glfw-3.2.1/freetype-2.9.1/include

DIRS =	parsing \
		glfw_wrapper \
		minimap \
		vector \
		graphic \
		graphic/draw \
		graphic/pen

INCDIRS = $(addprefix -I,$(INC))

OBJDIR = obj

OBJECTS = $(SRCFILES:%.c=$(OBJDIR)/%.o)

INCLUDES := inc/glfw_wrapper.h

SRCDIRS := $(addprefix src/,$(DIRS))

GLFWLIB := glfw-3.2.1/src/libglfw3.a

GLADLIB := glfw-3.2.1/glad/libglad.a

FT2LIB := glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.a

vpath %.c src $(SRCDIRS)

all: $(NAME)

$(NAME): libft/libft.a $(GLFWLIB) $(GLADLIB) $(FT2LIB) $(OBJECTS) Makefile
	$(CC) $(INCDIRS) $(CLIB) -o $@ $(OBJECTS)

$(OBJDIR)/%.o : %.c $(INCLUDES) | $(OBJDIR)
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

$(FT2LIB):
	cd glfw-3.2.1/freetype-2.9.1; \
	./configure; \
	make; \
	install_name_tool -id "glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib" glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib; \
	cd ..

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -w -C libft/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -w -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re