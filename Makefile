include Makefiles/default_var.mk

NAME := wolf3d

CFLAGS += -Iinc -Iglfw-3.2.1/include -Iglfw-3.2.1/glad/include -Ilibft -Iglfw-3.2.1/freetype-2.9.1/include -Iportaudio/include -Iportaudio/dr_wav -Ilibsjson/inc
CLIB += libft/libft.a libsjson/libsjson.a swiss-table/swiss_table.a
LDLIBS += glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib portaudio/lib/.libs/libportaudio.a portaudio/dr_wav/dr_wav.a glfw-3.2.1/src/libglfw3.a glfw-3.2.1/glad/libglad.a
Darwin_LDFLAGS += -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework Carbon -framework AudioUnit -framework AudioToolbox -framework CoreAudio

BLACK_LIST_SRCS += glfw-3.2.1/ \\./assets/ libft/ libsjson/ portaudio/ swiss-table/ original_main.c

include Makefiles/bin.mk

glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib:
	cd glfw-3.2.1/freetype-2.9.1; \
	./configure; \
	make; \
	cd ../..; \
	install_name_tool -id "glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib" glfw-3.2.1/freetype-2.9.1/objs/.libs/libfreetype.6.dylib;

glfw-3.2.1/src/libglfw3.a:
	cd glfw-3.2.1; \
	cmake CMakeLists.txt; \
	make; \
	cd ..

glfw-3.2.1/glad/libglad.a:
	cd glfw-3.2.1/glad/; \
	make; \
	cd ../..

portaudio/lib/.libs/libportaudio.a:
	cd portaudio; \
	./configure --disable-mac-universal; \
	make; \
	cd ..

portaudio/dr_wav/dr_wav.a:
	cd portaudio/dr_wav; \
	./compile.sh; \
	cd ../..
