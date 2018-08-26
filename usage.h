// #include "menu.h"

#include "terminal.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1024
menu_t* menu_generator();
void my_custom_write(const char* string, int slp);
