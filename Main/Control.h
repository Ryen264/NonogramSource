#ifndef CONTROL
#define CONTROL

#include "Global.h"

void GotoXY(int x = -1, int y = -1);
//Move skip:0, go:1, enter:2, swap:3, back:4
int Move(int mode = 0);

//int CouplePage(bool switch_file, int level);

#endif