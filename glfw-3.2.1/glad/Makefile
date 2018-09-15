all: libglad.a

libglad.a: src/glad.o
	ar rc libglad.a src/glad.o

src/glad.o: src/glad.c
	gcc -I include -c src/glad.c -o src/glad.o
