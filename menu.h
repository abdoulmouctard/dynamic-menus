typedef struct menu_s menu_t;
typedef struct item_s item_t;
typedef struct action_s action_t;
typedef unsigned int uint;

#define MAX_ITEM_SIZE 9

struct menu_s
{
  struct menu_s* parent;
  char * name;
  item_t *components;
  uint components_cpt; // max = MAX ^|
};

struct item_s
{
  enum {
    VOID=0, ACTION,MENU
  }type;

  union {
    struct menu_s* submenu;
    action_t* action;
  }content;
};

struct action_s
{
  char* name;
  void (*fonction) (void *);
};

menu_t* initialize_menu(const char* name);
void add_sub_menu(menu_t* parent_menu, menu_t* sub_menu);
void add_menu_action(menu_t* menu, const char* action_name, void(*fonction)(void*));
void delete_menu(menu_t* menu);
void go_back_menu(menu_t* menu);
void quit(menu_t *menu);
item_t* select_menu_item(menu_t* menu, int position);
void print(menu_t* menu, int file_desciptor);
void launch_menu(menu_t*menu);
void exec_menu_action(action_t* action, void * param);
