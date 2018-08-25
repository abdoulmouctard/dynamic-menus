#include "terminal.h"
#include <stdio.h>


int RUNNING = 1;



int main(int argc, char const *argv[])
{
  struct termios term;
  noncanonical_mode(&term);

  menu_t* menu = menu_generator();
  launch_menu(menu);

  delete_menu(menu);
  canonical_mode(&term);
  return 0;
}
