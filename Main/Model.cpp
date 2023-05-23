#include "Model.h"

//is full: true, unfull: false
bool CheckFull() {
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
			if (boardMat[i][j] == 0)
				return false;
	return true;
}
void AutoMark(vector<vector<int>> numsList, int** board) {
	if (board == NULL)
		board = boardMat;

	int count = 0;
	vector<int> tmp{};
	for (int j = 0; j < boardWidth; j++)
		if (board[boardY][j] == 1)
			count++;
		else {
			if (count != 0)
				tmp.push_back(count);
			count = 0;
		}
	if (count != 0)
		tmp.push_back(count);
	count = 0;

	//Add zeros after
	while (tmp.size() < (boardWidth + 1) / 2)
		tmp.push_back(0);

	//check row
	if (tmp == numsList[boardY]) {
		for (int j = 0; j < boardWidth; j++)
			if (board[boardY][j] == 0)
				board[boardY][j] = -1;
		return;
	}

	tmp.clear();
	for (int i = 0; i < boardHeight; i++)
		if (board[i][boardX] == 1)
			count++;
		else {
			if (count != 0)
				tmp.push_back(count);
			count = 0;
		}
	if (count != 0)
		tmp.push_back(count);
	count = 0;

	//Add zeros after
	while (tmp.size() < (boardHeight + 1) / 2)
		tmp.push_back(0);

	//check column
	if (tmp == numsList[boardHeight + boardX]) {
		for (int i = 0; i < boardHeight; i++)
			if (board[i][boardX] == 0)
				board[i][boardX] = -1;
	}
}

//numList = { <boardHeight lists of nums of rows>, <boardWidth lists of nums of columns>}
vector<vector<int>> GenerateNums(int** answerMat) {
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

		//Add zeros after
		while (tmp.size() < (boardWidth + 1) / 2)
			tmp.push_back(0);

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

		//Add zeros after
		while (tmp.size() < (boardHeight + 1) / 2)
			tmp.push_back(0);

		numsList.push_back(tmp);
	}
	return numsList;
}

int Single(int idGame) {
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
	int first_x = 10, first_y = 5;
	DrawBoard(first_x, first_y);
	DrawSide(numsList, first_x + 2, first_y - (boardHeight + 1) / 2, 0);
	DrawSide(numsList, first_x - boardWidth, first_y + 1, 1);

	////Hien thi thong so
	DrawFlagbox(first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 9 / 2, first_y + boardHeight + boardHeight + 1);
	DrawHealthnum(first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 17 / 2, first_y - boardHeight);
	ShowCur(1);

	screenX = first_x + 2; screenY = first_y + 1;
	boardX = boardY = 0;

	while (1) {
		int jumpX = 4, jumpY = 2;
		Display(0, 0, 50, 25);

		//right
		if ((GetAsyncKeyState(Key[0]) < 0) || (GetAsyncKeyState(Key[6]) < 0)) {
			while ((GetAsyncKeyState(Key[0]) < 0) || (GetAsyncKeyState(Key[6]) < 0));

			screenX = (boardX + 1 < boardWidth) ? (screenX + jumpX) : first_x + 2;
			boardX = (boardX + 1 < boardWidth) ? (boardX + 1) : 0;
			GotoXY();
		}

		//up
		if ((GetAsyncKeyState(Key[1]) < 0) || (GetAsyncKeyState(Key[7]) < 0)) {
			while ((GetAsyncKeyState(Key[1]) < 0) || (GetAsyncKeyState(Key[7]) < 0));

			screenY = (boardY - 1 >= 0) ? (screenY - jumpY) : first_y + 1 + 2 * (boardHeight - 1);
			boardY = (boardY - 1 >= 0) ? (boardY - 1) : boardHeight - 1;
			GotoXY();
		}

		//left
		if ((GetAsyncKeyState(Key[2]) < 0) || (GetAsyncKeyState(Key[8]) < 0)) {
			while ((GetAsyncKeyState(Key[2]) < 0) || (GetAsyncKeyState(Key[8]) < 0));

			screenX = (boardX - 1 >= 0) ? (screenX - jumpX) : first_x + 2 + 4 * (boardWidth - 1);
			boardX = (boardX - 1 >= 0) ? (boardX - 1) : boardWidth - 1;
			GotoXY();
		}

		//down
		if ((GetAsyncKeyState(Key[3]) < 0) || (GetAsyncKeyState(Key[9]) < 0)) {
			while ((GetAsyncKeyState(Key[3]) < 0) || (GetAsyncKeyState(Key[9]) < 0));

			screenY = (boardY + 1 < boardHeight) ? (screenY + jumpY) : first_y + 1;
			boardY = (boardY + 1 < boardHeight) ? (boardY + 1) : 0;
			GotoXY();
		}

		//enter
		if ((GetAsyncKeyState(Key[4]) < 0) || (GetAsyncKeyState(Key[10]) < 0)) {
			while ((GetAsyncKeyState(Key[4]) < 0) || (GetAsyncKeyState(Key[10]) < 0));

			if (boardMat[boardY][boardX] == 0) {
				boardMat[boardY][boardX] = answerMat[boardY][boardX];
				if (flag != answerMat[boardY][boardX]) {
					health--;
					DrawHealthnum(first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 17 / 2, first_y - boardHeight);
				}
				AutoMark(numsList);
			}
			DrawBoard(first_x, first_y);
		}

		//swap
		if ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0)) {
			while ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0));

			flag *= -1;
			DrawFlagbox(first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 9 / 2, first_y + boardHeight + boardHeight + 1);
		}

		//back
		if (GetAsyncKeyState(Key[12]) < 0) {
			while (GetAsyncKeyState(Key[12]) < 0);

			break;
		}

		if (health <= 0)
			//play again?
			return 0;

		if (CheckFull())
			//completed!
			return 2;
	}
	////save game
	return 1;
}

