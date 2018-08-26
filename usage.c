#include "usage.h"





void* quit_menu(void * p)
{
  my_custom_write("Quitting menu ... Good Bye !!",2);
  RUNNING = 0;
}


void* function_1(void * param)
{
  my_custom_write("You clicked function : function_1",1);
  return NULL;
}
void* function_2(void * param)
{
  my_custom_write("You clicked function : function_2",1);
  return NULL;
}
void* function_3(void * param)
{
  my_custom_write("You clicked function : function_3",1);
  return NULL;
}
void* function_4(void * param)
{
  my_custom_write("You clicked function : function_4",1);
  return NULL;
}
void* function_5(void * param)
{
  my_custom_write("You clicked function : function_5",1);
  return NULL;
}
void* function_6(void * param)
{
  my_custom_write("You clicked function : function_6",1);
  return NULL;
}
void* function_7(void * param)
{
  my_custom_write("You clicked function : function_7",1);
  return NULL;
}
void* function_8(void * param)
{
  my_custom_write("You clicked function : function_8",1);
  return NULL;
}


menu_t* menu_generator()
{
  menu_t * menu = initialize_menu("MY CUSTOM SETTING");
  add_menu_action(menu,"New Window", (void *)&function_1,"You clicked function_1");
  add_menu_action(menu,"Open Folder", (void *)&function_2,"You clicked function_2");
  add_menu_action(menu,"Open File", (void *)&function_3,"You clicked function_3");
  add_menu_action(menu,"New File", (void *)&function_4,"You clicked function_4");
  add_menu_action(menu,"Help", (void *)&function_5,"You clicked function_5");

  menu_t * menu1 = initialize_menu("Sub Menu");
  add_menu_action(menu1,"Find word",(void *)&function_6,"You clicked function_6");
  add_menu_action(menu1,"Find File",(void *)&function_7,"You clicked function_7");

  add_menu_action(menu1,"Back",(void *)&go_back_menu,NULL);
  add_sub_menu(menu, menu1);
  add_menu_action(menu,"QUIT", (void *)&quit_menu,NULL);

  return menu;
}


void my_custom_write(const char* string, int slp)
{
  if (!string){return;}

  int n = strlen(string);
  if (n>0) {
    char buffer[BUFFER_SIZE] = {'\0'};
    write(STDOUT_FILENO, "\n\n\t\t\t\t ======================= \n",32);
    snprintf(buffer, BUFFER_SIZE,"\t\t\t%s\n", string);
    write(STDOUT_FILENO, buffer, BUFFER_SIZE);
  }

  if (slp) {
    sleep(slp);
  }
}
