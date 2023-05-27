#ifndef MODEL
#include "Model.h"
#endif
#ifndef CONTROL
#include "Control.h"
#endif
#ifndef VIEW
#include "View.h"
#endif

#ifndef GLOBAL
#define GLOBAL

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
using namespace std;

const int screenWidth = 121, screenHeight = 66;

//D-W-A-S:0-3, space:4, Q:5 left-up-right-down(39-38-37-40):6-9, enter:10, /:11 esc:12
const char Key[] = { 'D', 'W', 'A', 'S', 32, 'Q', 39, 38, 37, 40, 13, '/', 27 };
const wchar_t Lines[5][11] = {  {L'─', L'│', L'┼', L'┌', L'┐', L'└', L'┘', L'├', L'┤', L'┬', L'┴'},
								{L'━', L'┃', L'╋', L'┏', L'┓', L'┗', L'┛', L'┣', L'┫', L'┳', L'┻'},
								{L'═', L'║', L'╬', L'╔', L'╗', L'╚', L'╝', L'╠', L'╣', L'╦', L'╩'},
								{L'─', L'│', L'┼', L'╭', L'╮', L'╰', L'╯', L'├', L'┤', L'┬', L'┴'},
								{L'█', L'▐', L'▌', L'▄', L'▀', L'■', L'Χ', L'┠', L'┨', L'┯', L'┷'} };
const vector<wstring> Heart = {L" ▄ ▄ ",
							   L"█████",
							   L" ▀█▀ "};
const int DayMonth2023[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

extern WORD* screenColor;
extern wchar_t* screenBuffer;

extern int screenX, screenY;

extern int boardHeight, boardWidth;
extern int boardX, boardY, flag, health, hint;
extern int** boardMat;

extern int gameList[12 * 31];
extern int** gameLib[12 * 31];

char* int_to_pchar(int x);
char* merge_pchar(vector<const char*> arr_pchar);


const vector<wstring> SingleMode = {	L"███████╗██╗███╗   ██╗ ██████╗ ██╗     ███████╗    ███╗   ███╗ ██████╗ ██████╗ ███████╗",
										L"██╔════╝██║████╗  ██║██╔════╝ ██║     ██╔════╝    ████╗ ████║██╔═══██╗██╔══██╗██╔════╝",
										L"███████╗██║██╔██╗ ██║██║  ███╗██║     █████╗      ██╔████╔██║██║   ██║██║  ██║█████╗",
										L"╚════██║██║██║╚██╗██║██║   ██║██║     ██╔══╝      ██║╚██╔╝██║██║   ██║██║  ██║██╔══╝",
										L"███████║██║██║ ╚████║╚██████╔╝███████╗███████╗    ██║ ╚═╝ ██║╚██████╔╝██████╔╝███████╗",
										L"╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝╚══════╝    ╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝"};
// ▀ ▄ █
const vector<vector<wstring>> Alphabet3pixels = { {	L"▄▀▄",
													L"█▀█",
													L"▀ ▀" },
												  { L"█▀█",
													L"█▀▄",
													L"▀▀▀" },
												  { L"▄▀▀",
													L"█  ",
													L" ▀▀" },
												  { L"█▀▄",
													L"█ █",
													L"▀▀ " },
												  { L"█▀▀",
													L"█▀ ",
													L"▀▀▀" },
												  { L"█▀▀",
													L"█▀ ",
													L"▀  " },
												  { L"▄▀▀",
													L"█ ▄",
													L" ▀▀" },
												  { L"█ █",
													L"█▀█",
													L"▀ ▀" },
												  { L"▀█▀",
													L" █ ",
													L"▀▀▀" },
												  { L" ▀█",
													L"▄ █",
													L"▀▀▀" },
												  { L"█ █",
													L"█▀▄",
													L"▀ ▀" },
												  { L"█▄ ▄█",
													L"█ ▀ █",
													L"▀   ▀" },
												  { L"█▄  █",
													L"█ ▀▄█",
													L"▀   ▀" },
												  { L"█▀█",
													L"█ █",
													L"▀▀▀" },
												  { L"█▀█",
													L"█▀▀",
													L"▀  " },
												  { L"▄▀▀▄ ",
													L"█ ▄█ ",
													L" ▀▀▀▀" },
												  { L"█▀▄",
													L"█▀▄",
													L"▀ ▀" },
												  { L"█▀▀",
													L"▀▀█",
													L"▀▀▀" },
												  { L"▀█▀",
													L" █",
													L" ▀ " },
												  { L"█ █",
													L"█ █",
													L"▀▀▀" },
												  { L"█ █",
													L"█ █",
													L" ▀ " },
												  { L"█   █",
													L"█ █ █",
													L" ▀ ▀ " },
												  { L"█ █",
													L"▄▀▄",
													L"▀ ▀" },
												  { L"█ █",
													L"▀▄▀",
													L" ▀ " },
												  { L"▀▀█",
													L"▄▀ ",
													L"▀▀▀" } };
const vector<vector<wstring>> Number3pixels = { { L"█▀█",
												  L"█ █",
												  L"▀▀▀" },
												{ L"▄▄ ",
												  L" █ ",
												  L"▀▀▀" },
												{ L"▀▀▄",
												  L"▄▀ ",
												  L"▀▀▀" },
												{ L"▀▀█",
												  L" ▀▄",
												  L"▀▀▀" },
												{ L"█ █",
												  L"▀▀█",
												  L"  ▀ " },
												{ L"█▀▀",
												  L" ▀▄",
												  L"▀▀ " },
												{ L"█▀▀",
												  L"█▀█",
												  L"▀▀▀" },
												{ L"▀▀█",
												  L" ▄▀",
												  L" ▀ " },
												{ L"█▀█",
												  L"█▀█",
												  L"▀▀▀" },
												{ L"█▀█",
												  L"▀▀█",
												  L"▀▀▀" } };

#endif