//
// Created by Claudio on 06/05/2021.
//

#include "includes/MenuItem.h"
#include "includes/Screen.h"

static const char *get_name(struct MenuItem *this) {
    return this->name;
}

struct MenuItem* set_screen(struct MenuItem *this, struct Screen *screen) {
    this->screen = screen;
    return this;
}

void to_string(struct MenuItem *this) {
    if(this->screen != NULL) {
        fprintf(stdout, "Name: %s Name length: %d Screen: %s\n",
                this->name, this->name_lenght, this->screen->get_name(this->screen));
    } else {
        fprintf(stdout, "Name: %s Name length: %d\n",
                this->name, this->name_lenght);
    }
}

static struct MenuItem new(const char *name) {

    short str_len = strlen(name);

    if(str_len > MAX_NAME_LENGHT) {
        fprintf(stderr, "The max length of the name is %d", MAX_NAME_LENGHT);
        exit(-1);
    } else {
        return (struct MenuItem){
                .name = strdup(name),
                .name_lenght=str_len,
                .get_name=&get_name,
                .set_screen=&set_screen,
                .to_string=&to_string,
                .screen=NULL
        };
    }
}
const struct MenuItemClass MenuItem={.new=&new};
