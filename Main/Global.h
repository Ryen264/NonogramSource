#pragma once
#include "Model.h"
#include "Control.h"
#include "View.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//D-W-A-S:0-3, space:4, Q:5 left-up-right-down(38-40):6-9, enter:10, /:11 esc:12
const char Key[] = { 'D', 'W', 'A', 'S', 32, 'Q', 37, 38, 39, 40, 13, '/', 27};


const int screenHeight = 200, screenWidth = 100;
extern int screenX, screenY;

extern int boardHeight, boardWidth;
extern int boardX, boardY, flag, health;
extern int** boardMat;

extern int gameList[12][31];
