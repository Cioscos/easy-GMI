//
// Created by Claudio on 06/05/2021.
//

#include "includes/easy_GMI.h"

void calculate_sizes(struct GMI *this) {
    //TODO: Implement that it works just on windows
    //get_win_resolution is definied in utils.h
#if defined _WIN64 || defined _WIN32
    get_win_resolution(&this->columns, &this->rows);
#else
    fprintf(stderr, "U can't used this function on Windows platforms");
#endif
}

void get_sizes(struct GMI *this, short *rows, short *columns) {
    *rows = this->rows;
    *columns = this->columns;
}

void set_sizes(struct GMI *this, short rows, short columns) {
    //Implement type check
    this->rows=rows;
    this->columns=columns;
}

struct GMI* add_screen(struct GMI *this, struct Screen screen) {
    //push function to add a menuItem in the itemList
    short push_screen(screen_t *head, struct Screen screen);

    if(this->screenList == NULL) {
        this->screenList = (screen_t *) malloc(sizeof(screen_t));

        if(this->screenList == NULL) {
            fprintf(stderr, "Memory allocation error (row 24 easy_GMI.c)");
            exit(EXIT_FAILURE);
        } else {
            this->screenList->screen = screen;
            this->screenList->next = NULL;
            return this;
        }
    } else {
        if(!push_screen(this->screenList, screen)) {
            fprintf(stderr, "Memory allocation error (row 33 easy_GMI.c)");
            exit(EXIT_FAILURE);
        } else {
            return this;
        }
    }
}

void start(struct GMI *this) {
    void draw_screen(struct GMI *this);
    int set_first_screen(struct GMI *this);
    size_t get_screen_list_size(struct GMI *this);
    void signal_handler(int signal_value);

    //Set the signal handler
    signal(SIGINT, signal_handler);

    //Key pressed (arrow keys)
    int key;

    /*Check if there are multiple first screens
    * or if there aren't screens
    */
    if(!set_first_screen(this)) {
        fprintf(stderr, "No first screen set. Closing...");
        exit(EXIT_FAILURE);
    }

    if(get_screen_list_size(this) == 0) {
        fprintf(stderr, "No screen added. Closing");
        exit(EXIT_FAILURE);
    }

    //Check if rows and columns are defined
    if (this->rows == 0 && this->columns == 0) {
        fprintf(stderr, "Rows and columns are not defined. Closing...");
        exit(EXIT_FAILURE);
    }

    //get console sizes before main loop
    short rows, columns;
    get_win_resolution(&columns, &rows);

    //Draws for the first time the screen
    draw_screen(this);

    for(;;) {
        //each iteration calculate console size
        calculate_sizes(this);

        if(this->rows != rows || this->columns != columns) {
        #if defined _WIN64 || defined _WIN32
            clear_console();
        #else
            printf("\033[2J\033[1;1H");
        #endif // defined
            draw_screen(this);
            rows = this->rows;
            columns = this->columns;
        }

        if (kbhit()) {
            key=getch();
            if (key == 224) {
                do {
                    key=getch();
                } while(key==224);
                switch (key) {
                    case ESC:
                        return;
                    case UP:
                        printf("up");
                        break;
                    case LEFT:
                        printf("left");
                        break;
                    case RIGHT:
                        printf("right");
                        break;
                    case DOWN:
                        printf("down");
                        break;
                    default:
                        break;
                }
            } else {
                if(key == ESC) {
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}

void draw_screen(struct GMI *this) {
    void calculate_items_position(struct GMI *this, int boundaries_size);
    bool is_in_array(const int *n, item_position_t *head);

    //Calculate boundaries
    int top_bottom_boundaries = round((this->rows * TOP_PERCENTAGE_BOUNDARY) / 100);
    size_t n_items = this->current_screen->get_items_list_size(this->current_screen);
    struct MenuItem items[n_items];
    item_t *current = this->current_screen->items_list;

    //fill items array
    for(size_t i = 0; i < n_items; i++) {
        items[i] = current->item;
        current = current->next;
    }

    calculate_items_position(this, top_bottom_boundaries);

    //calculate vertical boundaries
    short spaces = (short) ceil((double) (this->columns) / 2);

    short current_item = 0;

    for(size_t row = 0; row < this->rows; row++) {
        for(size_t column = 0; column < this->columns; column++) {
            if(row == 0 || row == this->rows - 1 || column == 0 || column == this->columns - 1) {
                if((row == 0 || row == this->rows - 1) && (column == 0 || column == this->columns - 1)) {
                    if(row == this->rows -1 && column == this->columns - 1) {
                        continue;
                    }
                    putch(' ');
                } else {
                    putch('#');
                }
            } else {
                if(is_in_array((const int *) &row, this->item_pos_list)) {
                    if(current_item < n_items) {
                        short complete_spaces = this->columns - 2;
                        short space_before_item = (complete_spaces / 2) - items[current_item].name_lenght;

                        char *row_string = (char *) calloc(complete_spaces + 1, sizeof(char));

                        short index = 0;

                        for(short i = 0; i < space_before_item; i++) {
                            row_string[i] = ' ';
                            index++;
                        }
                        strcat(row_string, items[current_item].name);
                        index += items[current_item].name_lenght;
                        for(short i = index; i < complete_spaces; i++)
                            row_string[i] = ' ';

                        //print line
                        printf("%s", row_string);

                        current_item++;
                        //Ends line
                        column = this->columns - 2;
                        free(row_string);
                    } else {
                        putch(' ');
                    }
                } else {
                    putch(' ');
                }
            }
        }
    }
}

void print_screens(struct GMI *this) {
    screen_t *current = this->screenList;

    while(current != NULL) {
        current->screen.print_info(&current->screen);
        current = current->next;
    }
}

//private
int set_first_screen(struct GMI *this) {
    screen_t *current = this->screenList;
    bool first_found = false;

    while(current != NULL) {
        if(current->screen.is_first) {
            if(first_found) {
                current->screen.set_is_first(&current->screen, false);
            } else {
                first_found = true;
                this->current_screen = &current->screen;
                return 1;
            }
        }
        current = current->next;
    }

    if(!first_found) {
        return 0;
    }
}

struct Screen* get_first_screen(struct GMI *this) {
    screen_t *current = this->screenList;

    while(current != NULL) {
        if(current->screen.is_first) {
            return &current->screen;
        }
        current = current->next;
    }
}

size_t get_screen_list_size(struct GMI *this) {
    screen_t *current = this->screenList;
    size_t count = 0;

    while(current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void calculate_items_position(struct GMI *this, int boundaries_size) {
    void add_item_position(struct GMI *this, int position);
    void delete_item_position_list(item_position_t **head);

    int available_rows = this->rows - (boundaries_size * 2);
    int printable_items = (int) available_rows / ITEM_ROW_HEIGHT;

    if(this->item_pos_list != NULL)
        delete_item_position_list(&this->item_pos_list);

    short current_item_part = 0;
    short count_items_added = 0;
    for(size_t row = boundaries_size + 1; row < this->rows - boundaries_size; row++) {
        if(current_item_part == 1) {
            add_item_position(this, row);
            count_items_added++;
        }
        if(current_item_part == 2) {
            current_item_part = 0;
            /*if(count_items_added == printable_items)
                break;*/
        } else{
            current_item_part++;
        }
    }
}

void add_item_position(struct GMI *this, int position) {
    short push_position(item_position_t *head, int position);

    if(this->item_pos_list == NULL) {
        this->item_pos_list = (item_position_t*) malloc(sizeof(item_position_t));

        if(this->item_pos_list == NULL) {
            fprintf(stderr, "Memory allocation error. Closing...");
            exit(EXIT_FAILURE);
        } else {
            this->item_pos_list->item_position = position;
            this->item_pos_list->next = NULL;
        }
    } else {
        if(!push_position(this->item_pos_list, position)) {
            fprintf(stderr, "Memory allocation error. Closing...)");
            exit(EXIT_FAILURE);
        }
    }
}

short push_position(item_position_t *head, int position) {
    item_position_t *current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    //Adding new element
    current->next = (item_position_t *) malloc(sizeof(item_position_t));

    if(current->next == NULL) {
        fprintf(stderr, "Memory allocation error. Closing...");
        return 0;
    }
    current->next->item_position = position;
    current->next->next = NULL;

    return 1;
}

void delete_item_position_list(item_position_t **head) {
    item_position_t  *current = *head;
    item_position_t  *next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

short push_screen(screen_t *head, struct Screen screen) {
    screen_t *current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    //Adding the new element
    current->next = (screen_t *) malloc(sizeof(screen_t));

    if(current->next == NULL) {
        fprintf(stderr, "Memory allocation error (row 34 screen.c)");
        return 0;
    }
    current->next->screen = screen;
    current->next->next = NULL;

    return 1;
}

bool is_in_array(const int *n, item_position_t *head) {
    item_position_t *current = head;

    while(current != NULL) {
        if(*n == current->item_position)
            return true;
        current = current->next;
    }
    return false;
}

void signal_handler(int signal_value) {
    printf("Interrupt signal received (%d) from keyboard. Stopping process...", signal_value);
    exit(EXIT_SUCCESS);
}

static struct GMI new() {
    struct GMI ret = {
            .get_sizes=&get_sizes,
            .set_sizes=&set_sizes,
            .calculate_sizes=&calculate_sizes,
            .add_screen=&add_screen,
            .print_screens=&print_screens,
            .start=&start,
            .screenList=NULL,
            .item_pos_list=NULL,
            .current_screen=NULL,
            .is_first_screen=true,
            .rows=0,
            .columns=0
    };
#if defined _WIN64 || defined _WIN32
    calculate_sizes(&ret);
#endif // defined
    return ret;
}
const struct GMIClass GMI = {.new=&new};
