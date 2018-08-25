CC = gcc
EXEC = menu-run
FILES = menu.c menu.h main.c
FLAGS = -std=c11 -g

build: $(FILES)
	$(CC) -c menu.c $(FLAGS)
	$(CC) -c terminal.c $(FLAGS)
	$(CC) -o $(EXEC) main.c terminal.o menu.o $(FLAGS)

clean:
	rm -vf *.o $(EXEC)

rebuild: clean build
