#include "menu.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  menu_t * menu = initialize_menu("MENU PRINCIPALE");
  delete_menu(menu);
  return 0;
}
