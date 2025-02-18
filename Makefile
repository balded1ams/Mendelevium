CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude 
LDFLAGS=-lX11 -lXft -lXcomposite -lXrender

all: src/*
	$(CC) $(CFLAGS) -o main $? $(LDFLAGS)

clean:
	rm main
