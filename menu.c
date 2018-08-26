#include <string.h>
#include <stdlib.h>
#include "menu.h"

menu_t* initialize_menu(const char* name)
{
  int i;
  menu_t* p = malloc(sizeof(menu_t));

  if (!p) {
    // throw error
  }

  p->parent = NULL;
  p->name = malloc(strlen(name)+1);
  p->name = strcpy(p->name, name);
  p->components = malloc(sizeof(item_t) * MAX_ITEM_SIZE);

  if (!p->components) {
    // throw error
  }

  for (i = 0; i < MAX_ITEM_SIZE; i++) {
    p->components[i].type = VOID;
  }

  p->components_cpt = 0;

  return p;
}

/**
* @return
*/
void add_sub_menu(menu_t* parent_menu, menu_t* sub_menu)
{
  if (parent_menu->components_cpt < MAX_ITEM_SIZE - 1) {
    parent_menu->components[parent_menu->components_cpt].type = MENU;
    parent_menu->components[parent_menu->components_cpt].content.submenu = malloc(sizeof(menu_t*));

    if (!(parent_menu->components[parent_menu->components_cpt].content.submenu)) {
      // throw error
    }

    parent_menu->components[parent_menu->components_cpt].content.submenu = sub_menu;
    sub_menu->parent = parent_menu;
    parent_menu->components_cpt ++;
    return;
  }
  // throw error
}

/**
* @return
*/
void add_menu_action(menu_t* menu, const char* action_name, void(*fonction)(void*),void * param)
{
  if ( (menu->components_cpt) < MAX_ITEM_SIZE-1)
  {
    menu->components[menu->components_cpt].type = ACTION;
    menu->components[menu->components_cpt].content.action = (action_t *)malloc(sizeof(action_t));
    menu->components[menu->components_cpt].content.action->name = malloc(strlen(action_name)+1);
    strcpy(menu->components[menu->components_cpt].content.action->name,action_name);
    menu->components[menu->components_cpt].content.action->fonction = fonction;
    menu->components[menu->components_cpt].content.action->parameter = param;
    menu->components_cpt ++;
    return;
  }
  // throw error
}

/**
* @return
*/
void delete_menu(menu_t* menu)
{
  if (!menu) return;
  menu_t* parent = menu->parent;

  if (menu->components_cpt == 0) {
    menu->parent = NULL;
  }else{
    int cpt = 0;
    while ( cpt < menu->components_cpt ) {
      if( menu->components[cpt].type == MENU) {
        delete_menu(menu->components[cpt].content.submenu);
        // free (menu->components[cpt].content.submenu->name);
        free (menu->components[cpt].content.submenu);
      }else if (menu->components[cpt].type == ACTION) {
        free(menu->components[cpt].content.action->name);
        free(menu->components[menu->components_cpt].content.action);
      }
      cpt ++;
    }
  }
  free(menu->components);
  free(menu->name);
  free(menu);
}

/**
* @return
*/
void go_back_menu()
{
  if (CURRENT_MENU && CURRENT_MENU->parent){
    CURRENT_MENU = CURRENT_MENU->parent;
  }
}


menu_t* get_root_menu(menu_t * menu)
{
  if (!menu) return NULL;

  if (menu->parent) {
    return get_root_menu(menu->parent);
  }
  return menu;
}

/**
* @return
*/
item_t* select_menu_item(menu_t* menu, int position)
{
  if (position >= 0 && position < MAX_ITEM_SIZE) {
    return menu->components+position;
  }
  return NULL;
}

/**
*
*/
void exec_menu_action(action_t* action, void * param)
{
  if (action) {
    action->fonction(param);
  }
}

item_t* get_index_from_input(menu_t* menu,int n)
{
  if (!menu || menu->components_cpt == 0 || n<1 || n > MAX_ITEM_SIZE+1) return NULL;
  int cpt=0,i=0;

  for (; i < MAX_ITEM_SIZE; i++) {
    if (menu->components[i].type == ACTION || menu->components[i].type == MENU )cpt++;
    if (cpt==n)return menu->components+i;
  }
  return NULL;
}
