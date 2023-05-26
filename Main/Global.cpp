#include "Global.h"

WORD* screenColor = new WORD[screenWidth * screenHeight];
wchar_t* screenBuffer = new wchar_t[screenWidth * screenHeight];

int screenX, screenY;

int boardHeight, boardWidth;
int boardX, boardY, flag, health, hint;
int** boardMat;

int gameList[12 * 31] = { 0 };
int** gameLib[12 * 31]{};

char* int_to_pchar(int x) {
	vector<int> reNum{};
	for (; x != 0; x /= 10)
		reNum.push_back(x % 10);

	char* pchar = new char[reNum.size() + 1];
	if (pchar == NULL)
		return NULL;

	for (int i = 0; i < reNum.size(); i++)
		pchar[i] = reNum[reNum.size() - 1 - i] + '0';
	pchar[reNum.size()] = '\0';
	return pchar;
}
char* merge_pchar(vector<const char*> arr_pchar) {
	int lentMerge = 0;
	for (int i = 0; i < arr_pchar.size(); i++)
		lentMerge += strlen(arr_pchar[i]);
	char* pcharm = new char[lentMerge + 1];
	if (pcharm == NULL)
		return NULL;

	int first = 0;
	for (int i = 0; i < arr_pchar.size(); first += strlen(arr_pchar[i++]))
		strcpy(pcharm + first, arr_pchar[i]);
	pcharm[lentMerge] = '\0';
	return pcharm;
}