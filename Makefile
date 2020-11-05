SDL=`sdl-config --cflags --libs`
#GTK=`pkg-config --libs --cflags gtk+-2.0`
all:
	gcc main.c -o batalhao $(SDL) #$(GTK)
