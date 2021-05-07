//
// Created by Claudio on 06/05/2021.
//

#ifndef EASY_GMI_SCREEN_H
#define EASY_GMI_SCREEN_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MenuItem.h"

/* item is an element of a linked list of menuItem.
*  Each node is connected to the next and to the previous one.
*/
typedef struct node_item {
    struct node_item *next;
    struct MenuItem item;
} item_t;

//Screen class
struct Screen {
    //methods
    struct Screen* (*add_item)(struct Screen *this, struct MenuItem menuItem);
    void (*print_info)(struct Screen *this);
    const char* (*get_name)(struct Screen *this);
    bool (*get_is_first)(struct Screen *this);
    struct Screen* (*set_is_first)(struct Screen *this, bool first);
    size_t (*get_items_list_size)(struct Screen *this);

    //attributes
    item_t *items_list;
    bool is_first;
    const char *name;
};
extern const struct ScreenClass {
    struct Screen (*new)(const char *name);
} Screen;

#endif //EASY_GMI_SCREEN_H
