#include "Global.h"

int main()
{
	boardHeight = boardWidth = 5;
	int** answerMat = new int* [boardHeight];
	for (int i = 0; i < boardHeight; i++) {
		answerMat[i] = new int[boardWidth];
	}
	answerMat[0][0] = answerMat[0][1] = answerMat[0][2] = answerMat[1][1] = answerMat[1][2] = answerMat[2][4] = answerMat[3][0] = answerMat[3][2] = answerMat[3][4] = answerMat[4][0] = answerMat[4][2] = answerMat[4][4] = -1;
	answerMat[0][3] = answerMat[0][4] = answerMat[1][0] = answerMat[1][3] = answerMat[1][4] = answerMat[2][0] = answerMat[2][1] = answerMat[2][2] = answerMat[2][3] = answerMat[3][1] = answerMat[3][3] = answerMat[4][1] = answerMat[4][3] = 1;
	gameLib[0] = answerMat;


	Configure();
	ClearScreen();
    gameList[0] = Single(0);
	ShowCur(0);

	ShowCur(1);
	ShowScrollbar(1);
	system("Mode 120, 9001");
	exit(0);
    return 0;
}