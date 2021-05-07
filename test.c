//
// Created by Claudio on 06/05/2021.
//

#include "includes/easy_GMI.h"

int main(int argc, char *argv[]) {

    struct GMI gmi = GMI.new();
    struct Screen screen = Screen.new("Screen 1");
    struct MenuItem item = MenuItem.new("Item 1");
    struct MenuItem item1 = MenuItem.new("Item 2");
    struct MenuItem item2 = MenuItem.new("Item 3");
    screen.add_item(&screen, item)->add_item(&screen, item1)->add_item(&screen, item2);
    screen.set_is_first(&screen, true);

    gmi.add_screen(&gmi, screen);
    gmi.print_screens(&gmi);
    gmi.start(&gmi);

    return 0;
}
