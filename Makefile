CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude -I/usr/include/freetype2 -I/usr/include/libpng16
LDFLAGS=-lX11 -lXft


all: src/main.c 
	$(CC) $(CFLAGS) -o main $? $(LDFLAGS)

clean:
	rm main
