CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: main

run: main
	./main

main: main.o
	$(CC) $(CFLAGS) -o main main.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main *.o
