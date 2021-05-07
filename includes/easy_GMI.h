//
// Created by Claudio on 06/05/2021.
//

#ifndef EASY_GMI_EASY_GMI_H
#define EASY_GMI_EASY_GMI_H

#include <conio.h>
#include <stdbool.h>
#include <math.h>
#include <signal.h>
#include "utils.h"
#include "MenuItem.h"
#include "Screen.h"

//Defining keys
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27

#define TOP_PERCENTAGE_BOUNDARY 25
#define ITEM_ROW_HEIGHT 3

typedef struct node_screen {
    struct node_screen *next;
    struct Screen screen;
} screen_t;

typedef struct node_item_position {
    struct node_item_position *next;
    int item_position;
} item_position_t;

//Defining main class of file
struct GMI {
    //methods
    void (*get_sizes)(struct GMI *this, short *rows, short *columns);
    void (*set_sizes)(struct GMI *this, short rows, short columns);
    void (*calculate_sizes)(struct GMI *this);
    struct GMI* (*add_screen)(struct GMI *this, struct Screen screen);
    void (*print_screens)(struct GMI *this);
    void (*start)(struct GMI *this);

    //attributes
    struct Screen *current_screen;
    item_position_t *item_pos_list;
    screen_t *screenList;
    bool is_first_screen;
    short rows, columns;
};
//Class
extern const struct GMIClass {
    struct GMI (*new)();
} GMI;

#endif //EASY_GMI_EASY_GMI_H
