CC = gcc
EXEC = menu-run
FILES = menu.c menu.h main.c usage.c
FLAGS = -std=c11 -g

build: $(FILES)
	$(CC) -c menu.c $(FLAGS)
	$(CC) -c terminal.c $(FLAGS)
	$(CC) -c usage.c $(FLAGS)
	$(CC) -o $(EXEC) main.c terminal.o menu.o usage.o $(FLAGS)

clean:
	rm -vf *.o $(EXEC)

rebuild: clean build
