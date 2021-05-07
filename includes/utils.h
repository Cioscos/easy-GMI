//
// Created by Claudio on 06/05/2021.
//

#ifndef EASY_GMI_UTILS_H
#define EASY_GMI_UTILS_H

#if defined _WIN64 || defined _WIN32
#include <windows.h>

CONSOLE_SCREEN_BUFFER_INFO csbi;

/**
* It allows to obtain the resolution of the console window.
* It will works just using Windows OS.
* @param x: width
* @param y: height
*/
void get_win_resolution(short *x, short *y);

void clear_console();
#endif // defined

#endif //EASY_GMI_UTILS_H
