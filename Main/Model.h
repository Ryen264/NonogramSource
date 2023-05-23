#ifndef MODEL
#define MODEL

#include "Global.h"

//is full: true, unfull: false
bool CheckFull();
void AutoMark(vector<vector<int>> numsList, int** board = NULL);

//numList = { <boardHeight lists of nums of rows>, <boardWidth lists of nums of columns>}
vector<vector<int>> GenerateNums(int** answerMat);

int Single(int idGame);

#endif