all:
	gcc -c main.c $(sdl-config --cflags)
	gcc -o main.exe main.o $(sdl-config --libs)