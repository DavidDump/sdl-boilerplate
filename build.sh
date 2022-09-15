gcc -c main.c $(sdl2-config --cflags)
gcc -o main.exe main.o $(sdl2-config --libs)