#include "Model.h"

//is full: true, unfull: false
bool CheckFull() {
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
			if (boardMat[i][j] == 0)
				return false;
	return true;
}
void AutoMark(vector<vector<int>> numsList) {
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
		while (tmp.size() < (boardWidth + 1) % 2)
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
		while (tmp.size() < (boardHeight + 1) % 2)
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
	DrawBoard(10, 5);
	Display();

	//find maxSize of columns numsLists
	/*int maxSize = numsList[boardHeight].size();
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
	}*/

	////Hien thi thong so
	//cout << endl << "Flag : " << flag << endl;
	//cout << "Health : " << health << endl;
	//GotoXY(0, 0);

	//while (1) {
	//	int move = Move();
	//	//enter
	//	if (move == 2) {
	//		if (boardMat[boardY][boardX] == 0) {
	//			boardMat[boardY][boardX] = answerMat[boardY][boardX];
	//			if (flag != answerMat[boardY][boardX]) {
	//				health--;
	//				GotoXY(0, boardHeight + maxSize + 2);
	//				cout << "Health : " << health;
	//			}
	//		}
	//		AutoMark(numsList);
	//		GotoXY(0, 0);
	//		DrawBoard();
	//		GotoXY();
	//	}
	//	//swap
	//	if (move == 3) {
	//		GotoXY(0, boardHeight + maxSize + 1);
	//		cout << "Flag :   ";
	//		GotoXY(0, boardHeight + maxSize + 1);
	//		cout << "Flag : " << flag;
	//		GotoXY();
	//	}
	//	//back
	//	if (move == 4)
	//		break;

	//	if (health <= 0)
	//		//play again?
	//		return 0;

	//	if (CheckFull())
	//		//completed!
	//		return 2;
	//	Sleep(5);
	//}
	////save game
	return 1;
}

