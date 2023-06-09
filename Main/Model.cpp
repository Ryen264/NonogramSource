﻿#include "Model.h"

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
	int unit = 1;
	//if (listGame[idGame] == 1)
		//load data board, flag, health, boardX, boardY, screenX, screenY

	wstring nameGame = L"TEST GAME";
	Text(nameGame, screenWidth / 2 - nameGame.size() / 2, 1, 0, -1);
	wstring levelGame = L"easy";
	if (levelGame.size() < 6)
		levelGame = L' ' + levelGame + L' ';
	Text(levelGame, screenWidth / 2 - levelGame.size() / 2, 2, 13, -1);

	DrawBoard(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7);
	DrawSide(numsList, screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 + 2, 7, 0);
	DrawSide(numsList, screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 - boardWidth, (boardHeight + 1) / 2 + 8, 1);
	DrawHealthnum(screenWidth / 2 - 17 / 2, 3);

	DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
	DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

	DrawBackbutton();
	DrawOptionsbutton();

	screenX = screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 + 2; screenY = (boardHeight + 1) / 2 + 7 + 1;
	boardX = boardY = 0;
	GotoXY();

	ShowCur(1);
	Display();

	int BaOp = 0, FlHi = 0;

	while (1) {
		int jumpX = unit * 3 + 1, jumpY = unit + 1;

		//right
		if ((GetAsyncKeyState(Key[0]) < 0) || (GetAsyncKeyState(Key[6]) < 0)) {
			while ((GetAsyncKeyState(Key[0]) < 0) || (GetAsyncKeyState(Key[6]) < 0));

			if (BaOp != 0) {
				FlHi = 0;

				BaOp *= -1;
				if (BaOp == 1) {
					DrawBackbutton(6);
					DrawOptionsbutton();
				}
				else {
					DrawBackbutton();
					DrawOptionsbutton(6);
				}
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);
			} else if (FlHi != 0) {
				BaOp = 0;

				FlHi++;
				if (FlHi >= 4)
					FlHi = 1;

				if (FlHi == 1)
					flag = 1;
				else if (FlHi == 3)
					flag = -1;
				//else Hint

				if (FlHi == 1 || FlHi == 3) {
					DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, 6);
					DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				}
				else {
					DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
					DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, 6);
				}
				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			} else {
				screenX = (boardX + 1 < boardWidth) ? (screenX + jumpX) : screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 + 2;
				boardX = (boardX + 1 < boardWidth) ? (boardX + 1) : 0;
				GotoXY();
				Display(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7 + boardHeight * unit + boardHeight + 1);
			}
		}

		//up
		if ((GetAsyncKeyState(Key[1]) < 0) || (GetAsyncKeyState(Key[7]) < 0)) {
			while ((GetAsyncKeyState(Key[1]) < 0) || (GetAsyncKeyState(Key[7]) < 0));

			boardY--;
			if (boardY == -1) {
				//Back - Options
				ShowCur(0);
				FlHi = 0;

				BaOp = 1;

				DrawBackbutton(6);
				DrawOptionsbutton();
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);

				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			} else if (boardY == -2) {
				//Flag - Hints
				ShowCur(0);
				BaOp = 0;

				if (flag == 1)
					FlHi = 1;
				else
					FlHi = 3;

				DrawBackbutton();
				DrawOptionsbutton();
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);

				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, 6);
				DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			} else {
				ShowCur(1);
				BaOp = FlHi = 0;

				DrawBackbutton();
				DrawOptionsbutton();
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);

				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);

				if (boardY <= -3 || boardY >= boardHeight - 1) {
					boardY = boardHeight - 1;
					screenY = (boardHeight + 1) / 2 + 8 + 2 * (boardHeight - 1);
				} else
					screenY -= jumpY;
				GotoXY();
				Display(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7 + boardHeight * unit + boardHeight + 1);
			}
		}

		//left
		if ((GetAsyncKeyState(Key[2]) < 0) || (GetAsyncKeyState(Key[8]) < 0)) {
			while ((GetAsyncKeyState(Key[2]) < 0) || (GetAsyncKeyState(Key[8]) < 0));

			if (BaOp != 0) {
				FlHi = 0;

				BaOp *= -1;
				if (BaOp == 1) {
					DrawBackbutton(6);
					DrawOptionsbutton();
				} else {
					DrawBackbutton();
					DrawOptionsbutton(6);
				}
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);
			} else if (FlHi != 0) {
				BaOp = 0;

				FlHi--;
				if (FlHi <= 0)
					FlHi = 3;

				if (FlHi == 1)
					flag = 1;
				else if (FlHi == 3)
					flag = -1;
				//else Hint

				if (FlHi == 1 || FlHi == 3) {
					DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, 6);
					DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				} else {
					DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
					DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, 6);
				}
				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			} else {
				screenX = (boardX - 1 >= 0) ? (screenX - jumpX) : screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 + 2 + 4 * (boardWidth - 1);
				boardX = (boardX - 1 >= 0) ? (boardX - 1) : boardWidth - 1;
				GotoXY();
				Display(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7 + boardHeight * unit + boardHeight + 1);
			}
		}

		//down
		if ((GetAsyncKeyState(Key[3]) < 0) || (GetAsyncKeyState(Key[9]) < 0)) {
			while ((GetAsyncKeyState(Key[3]) < 0) || (GetAsyncKeyState(Key[9]) < 0));

			boardY++;
			if (boardY == boardHeight) {
				//Flag - Hints
				ShowCur(0);
				BaOp = 0;

				if (flag == 1)
					FlHi = 1;
				else
					FlHi = 3;

				DrawBackbutton();
				DrawOptionsbutton();
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);

				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, 6);
				DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			}
			else if (boardY == boardHeight + 1) {
				//Back - Options
				ShowCur(0);
				FlHi = 0;

				BaOp = 1;

				DrawBackbutton(6);
				DrawOptionsbutton();
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);

				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			} else {
				ShowCur(1);
				BaOp = FlHi = 0;

				DrawBackbutton();
				DrawOptionsbutton();
				Display(0, 0, 4, 2);
				Display(screenWidth - 5, 0, screenWidth - 1, 2);

				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 3, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 + 8, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);

				if (boardY >= boardHeight + 2 || boardY <= 0) {
					boardY = 0;
					screenY = (boardHeight + 1) / 2 + 8;
				} else
					screenY += jumpY;
				GotoXY();
				Display(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7 + boardHeight * unit + boardHeight + 1);
			}
		}

		//enter
		if ((GetAsyncKeyState(Key[4]) < 0) || (GetAsyncKeyState(Key[10]) < 0)) {
			while ((GetAsyncKeyState(Key[4]) < 0) || (GetAsyncKeyState(Key[10]) < 0));

			if (BaOp != 0) {
				//Back - Options
				FlHi = 0;

				if (BaOp == 1)
					break;
				else
					//Options
					break;
			} else if (FlHi != 0) {
				//Flag - Hints
				BaOp = 0;

				FlHi *= -1;
				flag *= -1;
				DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
				Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
			} else if (boardMat[boardY][boardX] == 0) {
				boardMat[boardY][boardX] = answerMat[boardY][boardX];
				if (flag != answerMat[boardY][boardX]) {
					health--;
					DrawHealthnum(screenWidth / 2 - 17 / 2, 3);
					Display(screenWidth / 2 - 17 / 2, 3, screenWidth / 2 + 17 / 2, 6);
				}
				AutoMark(numsList);
				DrawBoard(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7);
				Display(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7, screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7 + boardHeight * unit + boardHeight + 1);
			}
		}

		//swap
		if ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0)) {
			while ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0));

			flag *= -1;
			DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);
			Display(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8, screenWidth / 2 + 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 11);
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

