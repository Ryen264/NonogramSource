#include "Control.h"

void gotoXY(int x = screenX, int y = screenY)
{
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Move skip:0, go:1, enter:2, swap:3, back:4
int Move(int mode = 0) {
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
		gotoXY();
		return 1;
	}
	if (up) {
		screenY = (screenY - jumpY >= 0) ? (screenY - jumpY) : boardHeight - 1;
		boardY = (boardY - 1 >= 0) ? (boardY - 1) : boardHeight - 1;
		gotoXY();
		return 1;
	}
	if (left) {
		screenX = (screenX - jumpX >= 0) ? (screenX - jumpX) : 2* (boardWidth - 1);
		boardX = (boardX - 1 >= 0) ? (boardX - 1) : boardWidth - 1;
		gotoXY();
		return 1;
	}
	if (down) {
		screenY = (screenY + jumpY < boardHeight) ? (screenY + jumpY) : 0;
		boardY = (boardY + 1 < boardHeight) ? (boardY + 1) : 0;
		gotoXY();
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
void drawBoard() {
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
//is full: true, unfull: false
bool checkFull() {
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
			if (boardMat[i][j] == 0)
				return false;
	return true;
}
void autoMark(vector<vector<int>> numsList) {
	int count = 0;
	vector<int> tmp{};
	for (int j = 0; j < boardWidth; j++)
		if (boardMat[boardY][j] == 1)
			count++;
		else {
			if (count != 0)
				tmp.push_back(count);
			count = 0;
		}
	if (count != 0)
		tmp.push_back(count);
	count = 0;

	if (tmp == numsList[boardY]) {
		for (int j = 0; j < boardWidth; j++)
			if (boardMat[boardY][j] == 0)
				boardMat[boardY][j] = -1;
		return;
	}

	tmp.clear();
	for (int i = 0; i < boardHeight; i++)
		if (boardMat[i][boardX] == 1)
			count++;
		else {
			if (count != 0)
				tmp.push_back(count);
			count = 0;
		}
	if (count != 0)
		tmp.push_back(count);
	count = 0;

	if (tmp == numsList[boardHeight + boardX]) {
		for (int i = 0; i < boardHeight; i++)
			if (boardMat[i][boardX] == 0)
				boardMat[i][boardX] = -1;
	}
}

//numList = { <boardHeight lists of nums of rows>, <boardWidth lists of nums of columns>}
vector<vector<int>> generateNums(int** answerMat) {
	vector<vector<int>> numsList;
	int count = 0;
	for (int i = 0; i < boardHeight; i++) {
		vector<int> tmp{};
		for (int j = 0; j < boardWidth; j++)
			if (answerMat[i][j] == 1)
				count++;
			else {
				if (count != 0)
					tmp.push_back(count);
				count = 0;
			}
		if (count != 0)
			tmp.push_back(count);
		count = 0;

		numsList.push_back(tmp);
	}
	for (int j = 0; j < boardWidth; j++) {
		vector<int> tmp{};
		for (int i = 0; i < boardHeight; i++)
			if (answerMat[i][j] == 1)
				count++;
			else {
				if (count != 0)
					tmp.push_back(count);
				count = 0;
			}
		if (count != 0)
			tmp.push_back(count);
		count = 0;

		numsList.push_back(tmp);
	}
	return numsList;
}

int testSingle(int day, int month) {
	if (gameList[month - 1][day - 1] == 2)
		return 2;

	//Vi du: 5 x 5
	boardHeight = boardWidth = 5;
	//Lay tu thu vien anh
	int** answerMat = new int* [boardHeight];
	for (int i = 0; i < boardHeight; i++) {
		answerMat[i] = new int[boardWidth];
	}
	answerMat[0][0] = answerMat[0][1] = answerMat[0][2] = answerMat[1][1] = answerMat[1][2] = answerMat[2][4] = answerMat[3][0] = answerMat[3][2] = answerMat[3][4] = answerMat[4][0] = answerMat[4][2] = answerMat[4][4] = -1;
	answerMat[0][3] = answerMat[0][4] = answerMat[1][0] = answerMat[1][3] = answerMat[1][4] = answerMat[2][0] = answerMat[2][1] = answerMat[2][2] = answerMat[2][3] = answerMat[3][1] = answerMat[3][3] = answerMat[4][1] = answerMat[4][3] = 1;
	//Get numsList
	vector<vector<int>> numsList = generateNums(answerMat);

	//initialize matrix
	boardMat = new int* [boardHeight];
	for (int i = 0; i < boardHeight; i++) {
		boardMat[i] = new int[boardWidth];
		memset(boardMat[i], 0, boardWidth * sizeof(int));
	}
	health = 3; flag = 1; boardX = 0; boardY = 0;
	//if (listGame[month - 1][day - 1] == 1)
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
	gotoXY(0, 0);

	while (1) {
		int move = Move();
		//enter
		if (move == 2) {
			if (boardMat[boardY][boardX] == 0) {
				boardMat[boardY][boardX] = answerMat[boardY][boardX];
				if (flag != answerMat[boardY][boardX]) {
					health--;
					gotoXY(0, boardHeight + maxSize + 2);
					cout << "Health : " << health;
				}
			}
			autoMark(numsList);
			gotoXY(0, 0);
			drawBoard();
			gotoXY();
		}
		//swap
		if (move == 3) {
			gotoXY(0, boardHeight + maxSize + 1);
			cout << "Flag :   ";
			gotoXY(0, boardHeight + maxSize + 1);
			cout << "Flag : " << flag;
			gotoXY();
		}
		//back
		if (move == 4)
			break;

		if (health <= 0)
			//play again?
			return 0;

		if (checkFull())
			//completed!
			return 2;
		Sleep(5);
	}
	//save game
	return 1;
}
