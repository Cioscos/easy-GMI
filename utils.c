//
// Created by Claudio on 06/05/2021.
//

#include "includes/utils.h"

#if defined _WIN64 || defined _WIN32
void get_win_resolution(short *x, short *y) {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void clear_console() {
    HANDLE h;
    CHAR_INFO v3;
    COORD v4;
    SMALL_RECT v5;

    if ((h = (HANDLE)GetStdHandle(0xFFFFFFF5), (unsigned int)GetConsoleScreenBufferInfo(h, &csbi)))
    {
        v5.Right = csbi.dwSize.X;
        v5.Bottom = csbi.dwSize.Y;
        v3.Char.UnicodeChar = 32;
        v4.Y = -csbi.dwSize.Y;
        v3.Attributes = csbi.wAttributes;
        v4.X = 0;
        *(DWORD *)&v5.Left = 0;
        ScrollConsoleScreenBufferW(h, &v5, 0, v4, &v3);
        csbi.dwCursorPosition.X = 0;
        csbi.dwCursorPosition.Y = 0;
        HANDLE v1 = GetStdHandle(0xFFFFFFF5);
        SetConsoleCursorPosition(v1, csbi.dwCursorPosition);
    }
}
#endif // defined

short is_longer_than(char *string, size_t limit) {
    //prototype
    size_t _strlen(char * s);

    size_t len = strlen(string);
    if(len > limit)
        return 1;

    return 0;
}

size_t _strlen(char * s) {
    char *p = s;
    for (; *p != '\0'; p++) {}
    return p - s;
}
