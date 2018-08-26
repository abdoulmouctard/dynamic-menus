#include "usage.h"

int RUNNING = 1;
menu_t* CURRENT_MENU;


int main(int argc, char const *argv[])
{
  struct termios term;
  // noncanonical_mode(&term);
  CURRENT_MENU = menu_generator();
  launch_menu(CURRENT_MENU);
  delete_menu(CURRENT_MENU);
  // canonical_mode(&term);
  return 0;
}
