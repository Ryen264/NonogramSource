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


//Ham CouplePage_Tinh trang: Dang hoan thien
/*
int CouplePage(bool switch_file, int level){

	ClearScreen();

	int index{};


	if (!switch_file) {
		ReadData(filegame);
		RandPic(index);
		boardMat = new int* [boardHeight];
		for (int i = 0; i < boardHeight; i++) {
			boardMat[i] = new int[boardWidth];
			memset(boardMat[i], 0, boardWidth * sizeof(int));
		}
		health = 3; flag = 1; boardX = 0; boardY = 0;
		modeplayer1 = 1, modeplayer2 = 0;
		wstring Content{};
		const char* Title = "Content: ";
		for (int i = 0; i < strlen(Title); i++) {
			Content.push_back(Title[i]);
		}
		for (int i = 0; i < strlen(filegame[index].content); i++) {
			Content.push_back(filegame[index].content[i]);
		}
		//Text(Content, 4, 0, first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 17 / 2 + 4, 0);
	}
	else {
		LoadGame();
	}

	if (!answerMat) {
		Text(L"Cannot load file", 4, 0, 0, 0);
		return 0;
	}

	int unit = 1;
	int first_x = screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, first_y = (boardHeight + 1) / 2 + 7;

	vector<vector<int>> numsList = GenerateNums(answerMat);

	//Ve Man Hinh
	DrawBackbutton();
	DrawOptionsbutton();

	hint = 26;
	DrawHintbox(screenWidth / 2 + (3 * boardWidth * unit + boardWidth + 1) / 2 - 4, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);

	//Ve ban choi
	DrawBoard(screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2, (boardHeight + 1) / 2 + 7);
	DrawSide(numsList, screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 + 2, 7, 0);
	DrawSide(numsList, screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 - boardWidth, (boardHeight + 1) / 2 + 8, 1);

	////Hien thi thong so
	DrawFlagbox(screenWidth / 2 - 9 / 2, (boardHeight + 1) / 2 + boardHeight * unit + boardHeight + 1 + 8);


	DrawHealthnum(screenWidth / 2 - 17 / 2, 3);
	//

	screenX = screenWidth / 2 - (3 * boardWidth * unit + boardWidth + 1) / 2 + 2; screenY = (boardHeight + 1) / 2 + 7 + 1;
	boardX = boardY = 0;
	GotoXY();
	ShowCur(1);

	Display();

	int countden1[2]{}, countden2[2]{};
	int prehealth=health;
	int preX=boardX;
	int preY=boardY;

	while (1) {
		int jumpX = 4, jumpY = 2;

		if (modeplayer1) {

			//right
			if ((GetAsyncKeyState(Key[0]) < 0)) {
				while ((GetAsyncKeyState(Key[0]) < 0));

				screenX = (boardX + 1 < boardWidth) ? (screenX + jumpX) : first_x + 2;
				boardX = (boardX + 1 < boardWidth) ? (boardX + 1) : 0;
				GotoXY();
			}

			//up
			if ((GetAsyncKeyState(Key[1]) < 0)) {
				while ((GetAsyncKeyState(Key[1]) < 0));

				screenY = (boardY - 1 >= 0) ? (screenY - jumpY) : first_y + 1 + 2 * (boardHeight - 1);
				boardY = (boardY - 1 >= 0) ? (boardY - 1) : boardHeight - 1;
				GotoXY();
			}

			//left
			if ((GetAsyncKeyState(Key[2]) < 0)) {
				while ((GetAsyncKeyState(Key[2]) < 0));

				screenX = (boardX - 1 >= 0) ? (screenX - jumpX) : first_x + 2 + 4 * (boardWidth - 1);
				boardX = (boardX - 1 >= 0) ? (boardX - 1) : boardWidth - 1;
				GotoXY();
			}

			//down
			if ((GetAsyncKeyState(Key[3]) < 0)) {
				while ((GetAsyncKeyState(Key[3]) < 0));

				screenY = (boardY + 1 < boardHeight) ? (screenY + jumpY) : first_y + 1;
				boardY = (boardY + 1 < boardHeight) ? (boardY + 1) : 0;
				GotoXY();
			}

			//enter
			if ((GetAsyncKeyState(Key[4]) < 0)) {
				while ((GetAsyncKeyState(Key[4]) < 0));

				if (boardMat[boardY][boardX] == 0) {
					boardMat[boardY][boardX] = answerMat[boardY][boardX];

					if (flag != answerMat[boardY][boardX]) {
						health--;
						DrawHealthnum(screenWidth / 2 - 17 / 2, 3);
					}

					if (boardMat[boardY][boardX] == 1 && prehealth == health) {
						if (preX == boardX) {
							countden1[1]++;
						}
						if (preY == boardY) {
							countden1[0]++;
						}
					}

					preX = boardX;
					preY = boardY;

					AutoMark(numsList);
				}

				if (prehealth > health) {
					modeplayer1 = 0;
					modeplayer2 = 1;
				}

				prehealth = health;

				for (int i = 0; i < numsList[boardX + boardHeight].size(); i++) {
					if (countden1[1] == numsList[boardX + boardHeight][i]&& countden1[1]>0) {
						countden1[1] = 0;
						modeplayer1 = 0;
						modeplayer2 = 1;
						break;
					}
				}

				for (int i = 0; i < numsList[boardY].size(); i++) {
					if (countden1[0] == numsList[boardY][i] && countden1[0] > 0) {
						countden1[0] = 0;
						modeplayer1 = 0;
						modeplayer2 = 1;
						break;
					}
				}

				DrawBoard(first_x, first_y);
				Display();
			}

			//swap
			if ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0)) {
				while ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0));
				flag *= -1;
				DrawFlagbox(first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 9 / 2 + 4, first_y + boardHeight + boardHeight + 1);
				Display();
			}

			//back
			if (GetAsyncKeyState(Key[12]) < 0) {
				while (GetAsyncKeyState(Key[12]) < 0);

				break;
			}

			//save game
			if (GetAsyncKeyState(Key[13]) < 0) {
				while (GetAsyncKeyState(Key[13]) < 0);
				SaveGame();
			}
		}
		else {
			//right
			if ((GetAsyncKeyState(Key[6]) < 0)) {
				while ((GetAsyncKeyState(Key[6]) < 0));

				screenX = (boardX + 1 < boardWidth) ? (screenX + jumpX) : first_x + 2;
				boardX = (boardX + 1 < boardWidth) ? (boardX + 1) : 0;
				GotoXY();
			}

			//up
			if ((GetAsyncKeyState(Key[7]) < 0)) {
				while ((GetAsyncKeyState(Key[7]) < 0));

				screenY = (boardY - 1 >= 0) ? (screenY - jumpY) : first_y + 1 + 2 * (boardHeight - 1);
				boardY = (boardY - 1 >= 0) ? (boardY - 1) : boardHeight - 1;
				GotoXY();
			}

			//left
			if ((GetAsyncKeyState(Key[8]) < 0)) {
				while ((GetAsyncKeyState(Key[8]) < 0));

				screenX = (boardX - 1 >= 0) ? (screenX - jumpX) : first_x + 2 + 4 * (boardWidth - 1);
				boardX = (boardX - 1 >= 0) ? (boardX - 1) : boardWidth - 1;
				GotoXY();
			}

			//down
			if ((GetAsyncKeyState(Key[9]) < 0)) {
				while ((GetAsyncKeyState(Key[9]) < 0));

				screenY = (boardY + 1 < boardHeight) ? (screenY + jumpY) : first_y + 1;
				boardY = (boardY + 1 < boardHeight) ? (boardY + 1) : 0;
				GotoXY();
			}

			//enter
			if ((GetAsyncKeyState(Key[10]) < 0)) {
				while ((GetAsyncKeyState(Key[10]) < 0));

				if (boardMat[boardY][boardX] == 0) {
					boardMat[boardY][boardX] = answerMat[boardY][boardX];

					if (flag != answerMat[boardY][boardX]) {
						health--;
						DrawHealthnum(screenWidth / 2 - 17 / 2, 3);
					}

					if (boardMat[boardY][boardX] == 1 && prehealth == health) {
						if (preX == boardX) {
							countden2[1]++;
						}
						if (preY == boardY) {
							countden2[0]++;
						}
					}

					preX = boardX;
					preY = boardY;

					AutoMark(numsList);
				}

				if (prehealth > health) {
					modeplayer1 = 0;
					modeplayer2 = 1;
				}

				prehealth = health;

				for (int i = 0; i < numsList[boardX + boardHeight].size(); i++) {
					if (countden2[1] == numsList[boardX + boardHeight][i] && countden2[1] > 0 ) {
						countden2[1] = 0;
						modeplayer2 = 0;
						modeplayer1 = 1;
						break;
					}

				}

				for (int i = 0; i < numsList[boardY].size(); i++) {
					if (countden2[0] == numsList[boardY][i] && countden2[0] > 0) {
						countden2[0] = 0;
						modeplayer2 = 0;
						modeplayer1 = 1;
						break;
					}
				}

				DrawBoard(first_x, first_y);
				Display();
			}

			//swap
			if ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0)) {
				while ((GetAsyncKeyState(Key[5]) < 0) || (GetAsyncKeyState(Key[11]) < 0));
				flag *= -1;
				DrawFlagbox(first_x - boardWidth + (boardWidth * 3 + boardWidth + 1 + boardWidth) / 2 - 9 / 2 + 4, first_y + boardHeight + boardHeight + 1);
				Display();
			}

			//back
			if (GetAsyncKeyState(Key[12]) < 0) {
				while (GetAsyncKeyState(Key[12]) < 0);

				break;
			}

			//save game
			if (GetAsyncKeyState(Key[13]) < 0) {
				while (GetAsyncKeyState(Key[13]) < 0);
				SaveGame();
			}
		}



		if (health <= 0)
			//play again?
			return 0;

		if (CheckFull())
			//completed!
			return 2;


	}

	return 1;
}
*/
