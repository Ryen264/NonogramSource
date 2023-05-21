#include "Control.h"

void GotoXY(int x, int y)
{
	if (x < 0)
		x = screenX;
	if (y < 0)
		y = screenY;
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Move skip:0, go:1, enter:2, swap:3, back:4
int Move(int mode) {
	/*
	Buoc nhay screenX, screenY phu thuoc board's size
	*/
	int jumpX = 2, jumpY = 1;
	bool bKey[13]{};

	for (int i = 0; i < 13; i++)
	{
		if (bKey[i] = GetAsyncKeyState(Key[i]) < 0) {
			while (bKey[i]) {
				bKey[i] = GetAsyncKeyState(Key[i]) < 0;
			}
			bKey[i] = true;
		}
	}
	
	bool right, up, left, down;
	int swap, enter, back;
	switch (mode) {
	case 1:
		right = bKey[0]; up = bKey[1]; left = bKey[2]; down = bKey[3];
		enter = (bKey[4]) ? 2 : 0;
		swap  = (bKey[5]) ? 3 : 0;
		break;
	case 2:
		right = bKey[6]; up = bKey[7]; left = bKey[8]; down = bKey[9];
		enter = (bKey[10]) ? 2 : 0;
		swap  = (bKey[11]) ? 3 : 0;
		break;
	default:
		right	= (bKey[0] || bKey[6]);
		up		= (bKey[1] || bKey[7]);
		left	= (bKey[2] || bKey[8]);
		down	= (bKey[3] || bKey[9]);
		enter	= (bKey[4] || bKey[10]) ? 2 : 0;
		swap	= (bKey[5] || bKey[11]) ? 3 : 0;
	}
	back = (bKey[12]) ? 4 : 0;
	
	if (right) {
		screenX = (screenX + jumpX < 2 * boardWidth) ? (screenX + jumpX) : 0;
		boardX = (boardX + 1 < boardWidth) ? (boardX + 1) : 0;
		GotoXY();
		return 1;
	}
	if (up) {
		screenY = (screenY - jumpY >= 0) ? (screenY - jumpY) : boardHeight - 1;
		boardY = (boardY - 1 >= 0) ? (boardY - 1) : boardHeight - 1;
		GotoXY();
		return 1;
	}
	if (left) {
		screenX = (screenX - jumpX >= 0) ? (screenX - jumpX) : 2* (boardWidth - 1);
		boardX = (boardX - 1 >= 0) ? (boardX - 1) : boardWidth - 1;
		GotoXY();
		return 1;
	}
	if (down) {
		screenY = (screenY + jumpY < boardHeight) ? (screenY + jumpY) : 0;
		boardY = (boardY + 1 < boardHeight) ? (boardY + 1) : 0;
		GotoXY();
		return 1;
	}
	if (enter)
		return enter;
	if (swap) {
		flag *= -1;
		return swap;
	}
	if (back)
		return back;
	return 0;
}

//View
void DrawBoard() {
	const char black = 'O', white = 'X';
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			switch (boardMat[i][j]) {
			case 1:
				cout << black;
				break;
			case -1:
				cout << white;
				break;
			default:
				cout << ' ';
			}
			cout << '|';
		}
		cout << endl;
	}
}

//Model


int TestSingle(int idGame) {
	if (gameList[idGame] == 2)
		return 2;

	//Get numsList
	int** answerMat = gameLib[idGame];
	vector<vector<int>> numsList = GenerateNums(answerMat);

	//initialize matrix
	boardMat = new int* [boardHeight];
	for (int i = 0; i < boardHeight; i++) {
		boardMat[i] = new int[boardWidth];
		memset(boardMat[i], 0, boardWidth * sizeof(int));
	}
	health = 3; flag = 1; boardX = 0; boardY = 0;
	//if (listGame[idGame] == 1)
		//load data board, flag, health, boardX, boardY, screenX, screenY
	
	//Ve ban choi
	//drawBoard();
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++)
			cout << " |";
		for (int k = 0; k < numsList[i].size(); k++)
			cout << numsList[i][k];
		cout << endl;
	}
	//find maxSize of columns numsLists
	int maxSize = numsList[boardHeight].size();
	for (int j = 0; j < boardWidth; j++)
		if (maxSize < numsList[boardHeight + j].size())
			maxSize = numsList[boardHeight + j].size();

	for (int k = 0; k < maxSize; k++) {
		for (int j = 0; j < boardWidth; j++) {
			if (k < numsList[boardHeight + j].size())
				cout << numsList[boardHeight + j][k];
			else
				cout << ' ';
			cout << ' ';
		}
		cout << endl;
	}

	//Hien thi thong so
	cout << endl << "Flag : " << flag << endl;
	cout << "Health : " << health << endl;
	GotoXY(0, 0);

	while (1) {
		int move = Move();
		//enter
		if (move == 2) {
			if (boardMat[boardY][boardX] == 0) {
				boardMat[boardY][boardX] = answerMat[boardY][boardX];
				if (flag != answerMat[boardY][boardX]) {
					health--;
					GotoXY(0, boardHeight + maxSize + 2);
					cout << "Health : " << health;
				}
			}
			AutoMark(numsList);
			GotoXY(0, 0);
			DrawBoard();
			GotoXY();
		}
		//swap
		if (move == 3) {
			GotoXY(0, boardHeight + maxSize + 1);
			cout << "Flag :   ";
			GotoXY(0, boardHeight + maxSize + 1);
			cout << "Flag : " << flag;
			GotoXY();
		}
		//back
		if (move == 4)
			break;

		if (health <= 0)
			//play again?
			return 0;

		if (CheckFull())
			//completed!
			return 2;
		Sleep(5);
	}
	//save game
	return 1;
}

