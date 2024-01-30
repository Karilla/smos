#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define MAX_COL 25
#define MAX_ROW 80
#define VIDEO_ADDRESS 0xB8000
#define VIDEO_INDEX_REGISTER 0x3D4
#define VIDEO_INDEX_DATA 0x3D5

void clear_screen();
void print_simple_string(char* message);

#endif