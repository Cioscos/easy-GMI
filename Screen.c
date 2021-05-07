//
// Created by Claudio on 06/05/2021.
//

#include "includes/Screen.h"

//public
struct Screen* add_item(struct Screen *this, struct MenuItem menuItem) {
    //push function to add a menuItem in the itemList
    short push_item(item_t *head, struct MenuItem menuItem);

    if(this->items_list == NULL) {
        this->items_list = (item_t *) malloc(sizeof(item_t));

        if(this->items_list == NULL) {
            fprintf(stderr, "Memory allocation error (row 13 screen.c)");
            exit(EXIT_FAILURE);
        } else {
            this->items_list->item = menuItem;
            this->items_list->next = NULL;
            return this;
        }
    } else {
        if(push_item(this->items_list, menuItem)) {
            fprintf(stderr, "Memory allocation error (row 22 screen.c)");
            exit(EXIT_FAILURE);
        } else {
            return this;
        }
    }
    return 0;
}

void print_info(struct Screen *this) {
    void print_itemList(item_t *items_list);

    printf("Screen name: %s is_first: %s\nItems names:\n", this->name, this->is_first ? "true" : "false");
    print_itemList(this->items_list);
}

const char* get_name(struct Screen *this) {
    return this->name;
}

bool get_is_first(struct Screen *this) {
    return this->is_first;
}

struct Screen* set_is_first(struct Screen *this, bool first) {
    this->is_first = first;
    return this;
}

size_t get_items_list_size(struct Screen *this) {
    item_t *current = this->items_list;
    size_t count = 0;

    while(current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

//private
short push_item(item_t *head, struct MenuItem menuItem) {
    item_t *current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    //Adding the new element
    current->next = (item_t *) malloc(sizeof(item_t));

    if(current->next == NULL) {
        fprintf(stderr, "Memory allocation error (row 34 screen.c)");
        return 1;
    }
    current->next->item = menuItem;
    current->next->next = NULL;

    return 0;
}

void print_itemList(item_t *items_list) {
    item_t *current = items_list;

    if(current == NULL) {
        puts("\tNo items\n");
        return;
    }

    while(current != NULL) {
        printf("\t%s\n", current->item.get_name(&current->item));
        current = current->next;
    }
}

static struct Screen new(const char *name) {
    return (struct Screen){
            .add_item=&add_item,
            .print_info=&print_info,
            .get_name=&get_name,
            .get_is_first=&get_is_first,
            .set_is_first=&set_is_first,
            .get_items_list_size=&get_items_list_size,
            .items_list=NULL,
            .name=strdup(name),
            .is_first=false
    };
}
const struct ScreenClass Screen = {.new=&new};
