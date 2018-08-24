CC = gcc
EXEC = menu-run
FILES = menu.c menu.h main.c
FLAGS = -std=c11

build: $(FILES)
	$(CC) -c menu.c $(FLAGS)
	$(CC) -o $(EXEC) main.c menu.o $(FLAGS)

clean:
	rm -vf *.o $(EXEC)

rebuild: clean build
