#ifndef VIEW
#define VIEW

#include "Global.h"

void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void ShowCur(bool CursorVisibility);
void Configure();

void Display(int fromX = 0, int fromY = 0, int toX = screenWidth - 1, int toY = screenHeight - 1, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
void ClearScreen(int bgdColor = 2, int txtColor = 0, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
//no background color: bgdColor = -1
void Text(wstring wsContent, int bgdColor, int txtColor, int nPosX, int nPosY, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
//no background color: bgdColor = -1
void DrawObject(vector<wstring> wsContent, int bgdColor, int txtColor, int nPosX, int nPosY, wchar_t* pBuffer = NULL, WORD* pColor = NULL);

void DrawFrame(int width, int height, int first_x, int first_y, int line, int bgdColor = -1, int txtColor = 0, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
void DrawBoard(int first_x, int first_y, int numWidth = 0, int numHeight = 0, int unit = 1, int** board = NULL, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
//side up-left-down-right : 0 1 2 3
void DrawSide(vector<vector<int>> numsList, int first_x, int first_y, int side, int numWidth = 0, int numHeight = 0, int unit = 1, wchar_t* pBuffer = NULL, WORD* pColor = NULL);

void DrawBackbutton(int first_x = 0, int first_y = 0, int bgdColor = -1, int txtColor = 0, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
void DrawOptionsbutton(int first_x = screenWidth - 5, int first_y = 0, int bgdColor = -1, int txtColor = 0, wchar_t* pBuffer = NULL, WORD* pColor = NULL);

void DrawFlagbox(int first_x, int first_y, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
void DrawHealthnum(int first_x, int first_y, wchar_t* pBuffer = NULL, WORD* pColor = NULL);
void DrawHintbox(int first_x, int first_y, int bgdColor = -1, int txtColor = 0, int Hints = -1, wchar_t* pBuffer = NULL, WORD* pColor = NULL);

#endif