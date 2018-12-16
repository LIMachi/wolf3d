NAME = wolf3d

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

CLIB = -L libft -lft -L libsjson -lsjson -L glfw-3.2.1/src -lglfw3 -L glfw-3.2.1/glad -lglad -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework Carbon -framework AudioUnit -framework AudioToolbox -framework CoreAudio -L glfw-3.2.1/freetype-2.9.1/objs/.libs -lfreetype glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib portaudio/lib/.libs/libportaudio.a portaudio/dr_wav/dr_wav.a

SRCFILES = main.c \
		   glfw_new_window.c \
		   glfw_refresh_window.c \
		   glfw_env.c \
		   map_editor.c \
		   default_map.c \
		   glfw_remove_window.c \
		   draw_map.c \
		   load_map.c \
		   save_map.c \
		   rotate_2d.c \
		   draw_line.c \
		   color_blend.c \
		   draw_pixel.c \
		   draw_square.c \
		   pen_init.c \
		   draw_text.c \
		   get_pixel.c \
		   draw_char.c \
		   pen_set_font.c \
		   pen_set_work_area.c \
		   glfw_callbacks.c \
		   glfw_update_callbacks.c \
		   glfw_attach_callback.c \
		   bmp_file_load.c \
		   draw_bmp.c \
		   glfw_window_resize_video_buffer.c \
		   default_config.c \
		   load_config.c \
		   save_config.c \
		   gui_attach_button.c \
		   gui_attach_to_window.c \
		   gui_button.c \
		   gui_gui.c \
		   noop.c \
		   gui_key_catch.c

INC = inc \
	  glfw-3.2.1/include \
	  glfw-3.2.1/glad/include \
	  libft \
	  glfw-3.2.1/freetype-2.9.1/include \
	  portaudio/include \
	  portaudio/dr_wav \
	  libftjson/inc

DIRS =	parsing \
		glfw_wrapper \
		minimap \
		vector \
		graphic \
		graphic/draw \
		graphic/pen \
		graphic/bmp \
		gui

INCDIRS = $(addprefix -I,$(INC))

OBJDIR = obj

OBJECTS = $(SRCFILES:%.c=$(OBJDIR)/%.o)

INCLUDES := inc/glfw_wrapper.h \
			inc/wolf3d.h

SRCDIRS := $(addprefix src/,$(DIRS))

SJSONLIB := libsjson/libsjson.a

GLFWLIB := glfw-3.2.1/src/libglfw3.a

GLADLIB := glfw-3.2.1/glad/libglad.a

FT2LIB := glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.a

PORTAUDIOLIB := portaudio/lib/libportaudio.la

DR_WAVLIB := portaudio/dr_wav/dr_wav.a

vpath %.c src $(SRCDIRS)

all: $(NAME)

$(NAME): libft/libft.a $(GLFWLIB) $(GLADLIB) $(FT2LIB) $(DR_WAVLIB) $(PORTAUDIOLIB) $(SJSONLIB) $(OBJECTS) Makefile
	$(CC) $(INCDIRS) $(CLIB) -o $@ $(OBJECTS)

$(OBJDIR)/%.o : %.c $(INCLUDES) | $(OBJDIR)
	$(CC) $(INCDIRS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

libft/libft.a:
	$(MAKE) -w -C libft/

$(SJSONLIB):
	cd libsjson; \
	make; \
	cd ..

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
	cd ../..; \
	install_name_tool -id "glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib" glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib;

$(PORTAUDIOLIB):
	cd portaudio; \
	./configure --disable-mac-universal; \
	make; \
	cd ..

$(DR_WAVLIB):
	cd portaudio/dr_wav; \
	./compile.sh; \
	cd ../..

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -w -C libft/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -w -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
