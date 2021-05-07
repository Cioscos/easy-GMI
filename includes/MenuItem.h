//
// Created by Claudio on 06/05/2021.
//

#ifndef EASY_GMI_MENUITEM_H
#define EASY_GMI_MENUITEM_H

#define MAX_NAME_LENGHT 256
#define MAX_BUF_SIZE 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Screen;

//Defining menu item class
struct MenuItem {
    //methods
    const char* (*get_name)(struct MenuItem *this);
    struct MenuItem* (*set_screen)(struct MenuItem *this, struct Screen *screen);
    void (*to_string)(struct MenuItem *this);

    //attributes
    struct Screen *screen;
    short name_lenght;
    const char *name;
};
extern const struct MenuItemClass {
    struct MenuItem (*new)(const char *name);
} MenuItem;

#endif //EASY_GMI_MENUITEM_H
