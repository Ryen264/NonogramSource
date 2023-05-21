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
	csbiex.ColorTable[6 ] = RGB(139, 0  , 0  );	//dark red
	csbiex.ColorTable[7 ] = RGB(255, 165, 0  );	//orange
	csbiex.ColorTable[8 ] = RGB(148, 0  , 211);	//dark violet
	csbiex.ColorTable[9 ] = RGB(255, 99 , 71 );	//tomato
	csbiex.ColorTable[10] = RGB(255, 128, 0  );	//orange (fox)
	csbiex.ColorTable[11] = RGB(60 , 179, 113);	//medium sea green
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
	cfiex.dwFontSize.Y = 24;
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
void ClearScreen(int bgdColor, int txtColor, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < screenWidth; i++)
		for (int j = 0; j < screenHeight; j++) {
			pBuffer[j * screenWidth + i] = L' ';
			pColor[j * screenWidth + i] = bgdColor * 16 + txtColor;
		}
}
void Text(wstring wsContent, int bgdColor, int txtColor, int nPosX, int nPosY, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < wsContent.length(); i++, nPosX++) {
		WORD wColor = (bgdColor >= 0) ? (bgdColor * 16 + txtColor) : ((pColor[nPosY * screenWidth + nPosX] / 16) * 16 + txtColor);
		pBuffer[nPosY * screenWidth + nPosX] = wsContent[i];
		if (pBuffer[nPosY * screenWidth + nPosX] != ' ')
			pColor[nPosY * screenWidth + nPosX] = wColor;
	}
}
void DrawObject(vector<wstring> contentsArr, int bgdColor, int txtColor, int nPosX, int nPosY, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	for (int i = 0; i < contentsArr.size(); i++)
		Text(contentsArr[i], bgdColor, txtColor, nPosX, nPosY + i, pBuffer, pColor);
}

void DrawFrame(int width, int height, int first_x, int first_y, wchar_t* pBuffer, WORD* pColor) {
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	pBuffer[first_y * screenWidth + first_x] = L'╔';
	for (int i = first_x + 1; i < first_x + width - 1; i++)
		pBuffer[first_y * screenWidth + i] = L'═';

	pBuffer[first_y * screenWidth + first_x + width - 1] = L'╗';
	for (int j = first_y + 1; j < first_y + height - 1; j++)
		pBuffer[j * screenWidth + first_x + width - 1] = L'║';

	pBuffer[(first_y + height - 1) * screenWidth + first_x + width - 1] = L'╝';
	for (int i = first_x + 1; i < first_x + width - 1; i++)
		pBuffer[(first_y + height - 1) * screenWidth + i] = L'═';

	pBuffer[(first_y + height - 1) * screenWidth + first_x] = L'╚';
	for (int j = first_y + 1; j < first_y + height - 1; j++)
		pBuffer[j * screenWidth + first_x] = L'║';
}
void DrawBoard(int first_x, int first_y, int numWidth, int numHeight, wchar_t* pBuffer, WORD* pColor, int unit) {
	if (numWidth == 0)
		numWidth = boardWidth;
	if (numHeight == 0)
		numHeight = boardHeight;
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	int width = numWidth * unit * 3 + numWidth + 1, height = numHeight * unit + numHeight + 1;
	DrawFrame(width + 4, height + 2, first_x, first_y);
	first_x += 2; first_y++;

	for (int i = first_x; i < first_x + width; i++)
		if (i % (5 * unit * 3 + 4 + 1) == first_x)
			pBuffer[first_y * screenWidth + i] = L'┳';
		else if (i % (unit * 3 + 1) == 0)
			pBuffer[first_y * screenWidth + i] = L'┯';
		else
			pBuffer[first_y * screenWidth + i] = L'━';
	
	for (int j = first_y; j < first_y + height; j++)
		if (j % (5 * unit + 4 + 1) == first_y)
			pBuffer[j * screenWidth + first_x] = L'┣';
		else if (j % (unit + 1) == 0)
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
	
	// ▗▄▄▄▖═══╗
	// ▐███▌ ╳ ║
	// ▝▀▀▀▘═══╝
	pBuffer[first_y					* screenWidth + first_x				] = L'┏';
	pBuffer[first_y					* screenWidth + first_x + width - 1	] = L'┓';
	pBuffer[(first_y + height - 1)	* screenWidth + first_x				] = L'┗';
	pBuffer[(first_y + height - 1)	* screenWidth + first_x + width - 1	] = L'┛';
}
//side up-left-down-right : 0 1 2 3
void DrawSide(vector<vector<int>> numsList, int first_x, int first_y, int side, int numWidth, int numHeight, wchar_t* pBuffer, WORD* pColor, int unit) {
	if (numWidth == 0)
		numWidth = boardWidth;
	if (numHeight == 0)
		numHeight = boardHeight;
	if (pBuffer == NULL)
		pBuffer = screenBuffer;
	if (pColor == NULL)
		pColor = screenColor;

	switch (side) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}