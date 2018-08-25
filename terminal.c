#include "terminal.h"
// #include "menu.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 50

extern int RUNNING;

void noncanonical_mode(struct termios *old)
{
    struct termios new;
    if (tcgetattr(STDIN_FILENO,old)==-1) {
      // throw error
      exit(11);
    }

    new.c_iflag=old->c_iflag;
    new.c_oflag=old->c_oflag;
    new.c_cflag=old->c_cflag;
    new.c_lflag=0;
    new.c_cc[VMIN]=1;
    new.c_cc[VTIME]=0;

    if(tcsetattr(STDIN_FILENO,TCSANOW,&new)==-1) {
      // throw error
      exit(12);
    }
    // sprintf(buf,"\e[?25l");
    // char buf[20];
    // write(file_desciptor,buf,strlen(buf));
}

void canonical_mode(struct termios *old)
{
    tcsetattr(STDIN_FILENO,TCSANOW,old);
    // char buf[20];
    // sprintf(buf,"\e[?25h");
    // write(file_desciptor,buf,strlen(buf));
}



void clean_buffer(char* buffer, int size)
{
  for (int i = 0; i < size; i++) {
    buffer[i] = ' ';
  }
}


void write_prompt(char* buffer,int buffer_size)
{
  clean_buffer(buffer,buffer_size);
  int n = sprintf(buffer, "\t\t\t>>>>>> ");
  write(STDOUT_FILENO, buffer, n+1);
}

void custom_write(char* buffer, int buffer_size)
{
  write(STDOUT_FILENO, "\t\t\t\t", 3);
  write(STDIN_FILENO, buffer, buffer_size);
  write(STDIN_FILENO, "\n", 1);
}

int cursor_start(int str_strlen, int buffer_size)
{
  if ( str_strlen >= buffer_size - 4 ) {
    return 0;
  }
  int tmp = buffer_size - str_strlen;

  return (tmp%2 == 0)?(tmp/2):(tmp-1)/2;
}

void print_item_new(char* buffer, int buffer_size, const char* string,int position)
{
  clean_buffer(buffer,buffer_size);
  int str_len = strlen(string);
  if (position>0 && position <= MAX_ITEM_SIZE) {
    snprintf(buffer+6, str_len+8, "[%d] - %s",position,string);
  }else{
    int start = cursor_start(strlen(string),buffer_size);
    snprintf(buffer+start-4, str_len+9, "[+] %s [+]",string);
  }

  buffer[0] = ':';
  buffer[1] = ':';
  buffer[buffer_size-1] = ':';
  buffer[buffer_size-2] = ':';

  custom_write(buffer,buffer_size);
}

void write_line_new(char* buffer, int buffer_size, char c, int full)
{
  clean_buffer(buffer,buffer_size);
  if (full != 0) {
    for (int i = 0; i < buffer_size-1; i++) {
      buffer[i] = c;
    }
  }else{
    buffer[0] = c;
    buffer[1] = c;

    buffer[buffer_size-1] = c;
    buffer[buffer_size] = c;
  }
  custom_write(buffer, buffer_size);
}

void print_menu(menu_t* menu)
{
  if (!menu) {
    return;
  }

  system("clear");

  char* buffer = malloc(sizeof(char)*BUFFER_SIZE);
  write_line_new(buffer, BUFFER_SIZE,':',1);
  print_item_new(buffer, BUFFER_SIZE, menu->name,0);
  write_line_new(buffer, BUFFER_SIZE,':',1);

  for (int i = 0; i < MAX_ITEM_SIZE; i++) {
    if (menu->components[i].type == MENU) {
      print_item_new(buffer, BUFFER_SIZE,menu->components[i].content.submenu->name,i+1);
    }else if (menu->components[i].type == ACTION) {
      print_item_new(buffer, BUFFER_SIZE,menu->components[i].content.action->name,i+1);
    }
  }
  write_line_new(buffer, BUFFER_SIZE,':',2);
  write_prompt(buffer, BUFFER_SIZE);
  free(buffer);
}

void launch_menu(menu_t* menu)
{
  while (RUNNING) {
    print_menu(menu);
    fgetc(stdin);
    break;
  }
  write(STDOUT_FILENO, "\n", 1);
}
