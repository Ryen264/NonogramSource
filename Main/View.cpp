#include "View.h"

void DisableResizeWindow() {
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void ShowScrollbar(BOOL Show) {
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}
void ShowCur(bool CursorVisibility) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(hStdout, &ConCurInf);
}
void Configure() {
	//Setup colors
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdout, &csbiex);

	csbiex.ColorTable[0 ] = RGB(0  , 0  , 0  );	//black
	csbiex.ColorTable[1 ] = RGB(135, 206, 250);	//light sky blue
	csbiex.ColorTable[2 ] = RGB(255, 255, 255);	//white
	csbiex.ColorTable[3 ] = RGB(0  , 100, 0  );	//dark green
	csbiex.ColorTable[4 ] = RGB(139, 69 , 19 );	//saddle brown (nau dam)
	csbiex.ColorTable[5 ] = RGB(205, 133, 63 );	//peru (nau nhat)
	csbiex.ColorTable[6 ] = RGB(255, 25 , 25 );	//red
	csbiex.ColorTable[7 ] = RGB(255, 165, 0  );	//orange
	csbiex.ColorTable[8 ] = RGB(148, 0  , 211);	//dark violet
	csbiex.ColorTable[9 ] = RGB(255, 99 , 71 );	//tomato
	csbiex.ColorTable[10] = RGB(255, 128, 0  );	//orange (fox)
	csbiex.ColorTable[11] = RGB(0  , 0  , 179);	//zaffre
	csbiex.ColorTable[12] = RGB(144, 238, 144);	//light green (xanh la nhat)
	csbiex.ColorTable[13] = RGB(149, 156, 176);	//con chon xanh binh thuong
	csbiex.ColorTable[14] = RGB(105, 115, 143);	//con chon xanh dam nhat
	csbiex.ColorTable[15] = RGB(203, 210, 227);	//con chon xanh nhat nhat

	SetConsoleScreenBufferInfoEx(hStdout, &csbiex);
	//

	//Disable Button
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);
	DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	ShowScrollbar(0);
	DisableResizeWindow();
	SetConsoleTitle(L"NONOGRAM Project _ J&R _ May&June23");
	//

	ShowCur(0);

	//Setup zoom
	CONSOLE_FONT_INFOEX cfiex;
	cfiex.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	GetCurrentConsoleFontEx(hStdout, 0, &cfiex);
	cfiex.dwFontSize.Y = 26;
	SetCurrentConsoleFontEx(hStdout, 0, &cfiex);
	//

	//Setup WindowSize & ScreenBufferSize
	RECT rectClient, rectWindow;
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);

	MoveWindow(hWnd, 80, 20, screenWidth, screenHeight, TRUE);

	system(merge_pchar({ "mode ", int_to_pchar(screenWidth), ", ", int_to_pchar(screenHeight)}));

	system("color 10");
	//

	srand(time(0));
}

void Display(int fromX, int fromY, int toX, int toY, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	for (int j = fromY; j <= toY; j++)
		for (int i = fromX; i <= toX; i++) {
			COORD cPos = { i ,j };
			WriteConsoleOutputAttribute(hStdout, &pColor [j * screenWidth + i], 1, cPos, &dwBytesWritten);
			WriteConsoleOutputCharacter(hStdout, &pBuffer[j * screenWidth + i], 1, cPos, &dwBytesWritten);
		}
}
void SetBufferColor(int x, int y, wchar_t LChar, int txtColor, int bgdColor, wchar_t*& pBuffer, WORD*& pColor) {
	pBuffer[y * screenWidth + x] = LChar;
	if (bgdColor < 0)
		bgdColor = pColor[y * screenWidth + x] / 16;
	pColor[y * screenWidth + x] = bgdColor * 16 + txtColor;
}

void ClearScreen(int txtColor, int bgdColor, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < screenWidth; i++)
		for (int j = 0; j < screenHeight; j++)
			SetBufferColor(i, j, L' ', txtColor, bgdColor, pBuffer, pColor);
}
void Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < wsContent.length(); i++, first_x++)
		SetBufferColor(first_x, first_y, wsContent[i], txtColor, bgdColor, pBuffer, pColor);
}
void DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < contentsArr.size(); i++)
		Text(contentsArr[i], first_x, first_y + i, txtColor, bgdColor, pBuffer, pColor);
}

void DrawBoard(int first_x, int first_y, int numWidth, int numHeight, int unit, int** board, wchar_t* pBuffer, WORD* pColor) {
	if (board == NULL)
		board = boardMat;
	if (numWidth == 0)
		numWidth = boardWidth;
	if (numHeight == 0)
		numHeight = boardHeight;
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	int width = numWidth * unit * 3 + numWidth + 1, height = numHeight * unit + numHeight + 1;

	for (int i = first_x; i < first_x + width; i++)
		if ((i - first_x) % (5 * unit * 3 + 4 + 1) == 0)
			pBuffer[first_y * screenWidth + i] = L'┳';
		else if ((i - first_x) % (unit * 3 + 1) == 0)
			pBuffer[first_y * screenWidth + i] = L'┯';
		else
			pBuffer[first_y * screenWidth + i] = L'━';
	
	for (int j = first_y; j < first_y + height; j++)
		if ((j - first_y) % (5 * unit + 4 + 1) == 0)
			pBuffer[j * screenWidth + first_x] = L'┣';
		else if ((j - first_y) % (unit + 1) == 0)
			pBuffer[j * screenWidth + first_x] = L'┠';
		else
			pBuffer[j * screenWidth + first_x] = L'┃';

	
	for (int j = first_y + 1; j < first_y + height; j++)
		for (int i = first_x + 1; i < first_x + width; i++)
			if ((j - first_y - 1) % (5 * unit + 4 + 1) == 5 * unit + 4)
				if ((i - first_x - 1) % (5 * unit * 3 + 4 + 1) == 5 * unit * 3 + 4)
					pBuffer[j * screenWidth + i] = L'╋';
				else if ((i - first_x - 1) % (unit * 3 + 1) == unit * 3)
					pBuffer[j * screenWidth + i] = L'┿';
				else
					pBuffer[j * screenWidth + i] = L'━';
			else if ((j - first_y - 1) % (unit + 1) == unit)
				if ((i - first_x - 1) % (5 * unit * 3 + 4 + 1) == 5 * unit * 3 + 4)
					pBuffer[j * screenWidth + i] = L'╂';
				else if ((i - first_x - 1) % (unit * 3 + 1) == unit * 3)
					pBuffer[j * screenWidth + i] = L'┼';
				else
					pBuffer[j * screenWidth + i] = L'─';
			else if ((i - first_x - 1) % (5 * unit * 3 + 4 + 1) == 5 * unit * 3 + 4)
				pBuffer[j * screenWidth + i] = L'┃';
				else if ((i - first_x - 1) % (unit * 3 + 1) == unit * 3)
				pBuffer[j * screenWidth + i] = L'│';


	for (int i = first_x + 1; i < first_x + width; i++)
		if ((i - first_x - 1) % (5 * unit * 3 + 4 + 1) == 5 * unit * 3 + 4)
			pBuffer[(first_y + height - 1) * screenWidth + i] = L'┻';
		else if ((i - first_x - 1) % (unit * 3 + 1) == unit * 3)
			pBuffer[(first_y + height - 1) * screenWidth + i] = L'┷';
	
	for (int j = first_y + 1; j < first_y + height; j++)
		if ((j - first_y - 1) % (5 * unit + 4 + 1) == 5 * unit + 4)
			pBuffer[j * screenWidth + first_x + width - 1] = L'┫';
		else if ((j - first_y - 1) % (unit + 1) == unit)
			pBuffer[j * screenWidth + first_x + width - 1] = L'┨';
	
	pBuffer[first_y					* screenWidth + first_x				] = L'┏';
	pBuffer[first_y					* screenWidth + first_x + width - 1	] = L'┓';
	pBuffer[(first_y + height - 1)	* screenWidth + first_x				] = L'┗';
	pBuffer[(first_y + height - 1)	* screenWidth + first_x + width - 1	] = L'┛';


	for (int i = 0, x = first_x + 2; i < boardWidth; i++, x += 4)
		for (int j = 0, y = first_y + 1; j < boardHeight; j++, y += 2)
			switch (board[j][i]) {
			case 1: {
				pBuffer[y * screenWidth + x - 1] = L'▐';
				pBuffer[y * screenWidth + x] = L'█';
				pBuffer[y * screenWidth + x + 1] = L'▌';
				break;
			}
			case -1:
				pBuffer[y * screenWidth + x] = L'Χ';
				break;
			}
}
void DrawSide(vector<vector<int>> numsList, int first_x, int first_y, int side, int numWidth, int numHeight, int unit, wchar_t* pBuffer, WORD* pColor) {
	if (numWidth == 0)
		numWidth = boardWidth;
	if (numHeight == 0)
		numHeight = boardHeight;
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	switch (side) {
	case 0: {
		for (int i = 0, x = first_x; i < boardWidth; i++, x += (unit * 3 + 1)) {
			vector<int> tmp = {};
			//find number of != 0
			int n = 0;
			while (numsList[boardHeight + i][n] != 0) n++;
			for (int j = 0; j < numsList[boardHeight + i].size() - n; j++)
				tmp.push_back(0);
			for (int j = 0; j < n; j++)
				tmp.push_back(numsList[boardHeight + i][j]);

			for (int j = 0, y = first_y; j < tmp.size(); j++, y++)
				if (tmp[j] != 0)
					pBuffer[y * screenWidth + x] = tmp[j] + L'0';
		}
		break;
	}
	case 1: {
		for (int j = 0, y = first_y; j < boardHeight; j++, y += (unit + 1)) {
			vector<int> tmp = {};
			//find number of != 0
			int n = 0;
			while (numsList[j][n] != 0) n++;
			for (int i = 0; i < numsList[j].size() - n; i++)
				tmp.push_back(0);
			for (int i = 0; i < n; i++)
				tmp.push_back(numsList[j][i]);

			for (int i = 0, x = first_x; i < tmp.size(); i++, x += 2)
				if (tmp[i] != 0)
					pBuffer[y * screenWidth + x] = tmp[i] + L'0';
		}
		break;
	}
	case 2: {
		for (int i = 0, x = first_x; i < boardWidth; i++, x += (unit * 3 + 1))
			for (int j = 0, y = first_y; j < numsList[boardHeight + i].size(); j++, y++)
				if (numsList[boardHeight + i][j] != 0)
					pBuffer[y * screenWidth + x] = numsList[boardHeight + i][j] + L'0';
				else
					break;
		break;
	}
	case 3: {
		for (int j = 0, y = first_y; j < boardHeight; j++, y += (unit + 1))
			for (int i = 0, x = first_x; i < numsList[j].size(); i++, x += 2)
				if (numsList[j][i] != 0)
					pBuffer[y * screenWidth + x] = numsList[j][i] + L'0';
				else
					break;
		break;
	}
	}
}

void DrawFrame(int width, int height, int first_x, int first_y, int line, int txtColor, int bgdColor, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	SetBufferColor(first_x, first_y, Lines[line][3], txtColor, bgdColor, pBuffer, pColor);
	for (int i = first_x + 1; i < first_x + width - 1; i++)
		SetBufferColor(i, first_y, Lines[line][0], txtColor, bgdColor, pBuffer, pColor);

	SetBufferColor(first_x + width - 1, first_y, Lines[line][4], txtColor, bgdColor, pBuffer, pColor);
	for (int j = first_y + 1; j < first_y + height - 1; j++)
		SetBufferColor(first_x + width - 1, j, Lines[line][1], txtColor, bgdColor, pBuffer, pColor);

	SetBufferColor(first_x + width - 1, first_y + height - 1, Lines[line][6], txtColor, bgdColor, pBuffer, pColor);
	for (int i = first_x + 1; i < first_x + width - 1; i++)
		SetBufferColor(i, first_y + height - 1, Lines[line][0], txtColor, bgdColor, pBuffer, pColor);

	SetBufferColor(first_x, first_y + height - 1, Lines[line][5], txtColor, bgdColor, pBuffer, pColor);
	for (int j = first_y + 1; j < first_y + height - 1; j++)
		SetBufferColor(first_x, j, Lines[line][1], txtColor, bgdColor, pBuffer, pColor);
}
void DrawHealthnum(int first_x, int first_y, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < health; i++, first_x += 6)
		DrawObject(Heart, 6, -1, first_x, first_y);
	for (int i = 0; i < 3 - health; i++, first_x += 6)
		DrawObject(Heart, 13, -1, first_x, first_y);
}

void DrawFlagbox(int first_x, int first_y, int txtColor, int bgdColor, int Flag, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;
	if (Flag == 0)
		Flag = flag;

	if (Flag == 1) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 3; j++)
				SetBufferColor(first_x + i, first_y + j, L' ', 0, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 2, first_y + 1, L'X', 0, bgdColor, pBuffer, pColor);


		for (int i = 1; i < 4; i++) {
			SetBufferColor(first_x + 4 + i, first_y, L'─', txtColor, bgdColor, pBuffer, pColor);
			SetBufferColor(first_x + 4 + i, first_y + 2, L'─', txtColor, bgdColor, pBuffer, pColor);
		}
		SetBufferColor(first_x + 4, first_y + 1, L'│', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 8, first_y + 1, L'│', txtColor, bgdColor, pBuffer, pColor);

		SetBufferColor(first_x + 4, first_y, L'╭', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 8, first_y, L'╮', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 4, first_y + 2, L'╰', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 8, first_y + 2, L'╯', txtColor, bgdColor, pBuffer, pColor);

		SetBufferColor(first_x + 5, first_y + 1, L'▐', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 6, first_y + 1, L'█', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 7, first_y + 1, L'▌', txtColor, bgdColor, pBuffer, pColor);
	}
	else {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 3; j++)
				SetBufferColor(first_x + 4 + i, first_y + j, L' ', 0, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 5, first_y + 1, L'▐', 0, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 6, first_y + 1, L'█', 0, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 7, first_y + 1, L'▌', 0, bgdColor, pBuffer, pColor);


		for (int i = 1; i < 4; i++) {
			SetBufferColor(first_x + i, first_y, L'─', txtColor, bgdColor, pBuffer, pColor);
			SetBufferColor(first_x + i, first_y + 2, L'─', txtColor, bgdColor, pBuffer, pColor);
		}
		SetBufferColor(first_x, first_y + 1, L'│', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 4, first_y + 1, L'│', txtColor, bgdColor, pBuffer, pColor);

		SetBufferColor(first_x, first_y, L'╭', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 4, first_y, L'╮', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x, first_y + 2, L'╰', txtColor, bgdColor, pBuffer, pColor);
		SetBufferColor(first_x + 4, first_y + 2, L'╯', txtColor, bgdColor, pBuffer, pColor);

		SetBufferColor(first_x + 2, first_y + 1, L'X', txtColor, bgdColor, pBuffer, pColor);
	}
}
void DrawHintbox(int first_x, int first_y, int txtColor, int bgdColor, int Hints, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;
	if (Hints < 0)
		Hints = hint;

	DrawFrame(5, 3, first_x, first_y, 3, txtColor, bgdColor, pBuffer, pColor);
	SetBufferColor(first_x + 2, first_y + 1, L'+', txtColor, bgdColor, pBuffer, pColor);

	wstring hintGame = to_wstring(Hints);
	Text(hintGame, first_x + 5 - hintGame.size(), first_y, txtColor, bgdColor, pBuffer, pColor);
}

void DrawBackbutton(int txtColor, int bgdColor, int first_x, int first_y, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	DrawFrame(5, 3, first_x, first_y, 3, txtColor, bgdColor, pBuffer, pColor);
	SetBufferColor(first_x + 2, first_y + 1, L'<', txtColor, bgdColor, pBuffer, pColor);
}
void DrawOptionsbutton(int txtColor, int bgdColor, int first_x, int first_y, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	DrawFrame(5, 3, first_x, first_y, 3, txtColor, bgdColor, pBuffer, pColor);
	SetBufferColor(first_x + 2, first_y + 1, L'?', txtColor, bgdColor, pBuffer, pColor);
}

void DrawMonthYear(int month, int year, int first_x, int first_y, int txtColor, int bgdColor, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;
	string strYear = to_string(year);

	switch (month) {
	case 1:
		DrawObject(Alphabet3pixels['J' - 'A'], first_x, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['A' - 'A'], first_x + 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['N' - 'A'], first_x + 8, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 16 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 2:
		DrawObject(Alphabet3pixels['F' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['E' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['B' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 3:
		DrawObject(Alphabet3pixels['M' - 'A'], first_x, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['A' - 'A'], first_x + 6, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['R' - 'A'], first_x + 10, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 16 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 4:
		DrawObject(Alphabet3pixels['A' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['P' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['R' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 5:
		DrawObject(Alphabet3pixels['M' - 'A'], first_x, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['A' - 'A'], first_x + 6, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['Y' - 'A'], first_x + 10, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 16 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 6:
		DrawObject(Alphabet3pixels['J' - 'A'], first_x, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['U' - 'A'], first_x + 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['N' - 'A'], first_x + 8, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 16 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 7:
		DrawObject(Alphabet3pixels['J' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['U' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['L' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 8:
		DrawObject(Alphabet3pixels['A' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['U' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['G' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 9:
		DrawObject(Alphabet3pixels['S' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['E' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['P' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 10:
		DrawObject(Alphabet3pixels['O' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['C' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['T' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 11:
		DrawObject(Alphabet3pixels['N' - 'A'], first_x, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['O' - 'A'], first_x + 6, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['V' - 'A'], first_x + 10, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 16 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	case 12:
		DrawObject(Alphabet3pixels['D' - 'A'], first_x + 1, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['E' - 'A'], first_x + 5, first_y, txtColor, bgdColor, pBuffer, pColor);
		DrawObject(Alphabet3pixels['C' - 'A'], first_x + 9, first_y, txtColor, bgdColor, pBuffer, pColor);

		for (int i = 0; i < strYear.size(); i++)
			DrawObject(Number3pixels[strYear[i] - '0'], first_x + 15 + i * 4, first_y, txtColor, bgdColor, pBuffer, pColor);
		break;
	}
}
void DrawSingleMode() {
	DrawBackbutton();
	DrawOptionsbutton();
	DrawObject(SingleMode, 3, -1, screenWidth / 2 - SingleMode[0].size() / 2, 0);

	//32/2
	//DrawMonthYear
}