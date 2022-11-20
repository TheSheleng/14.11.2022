#include "MainMenu.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(MainMenu::DialogID), NULL, (DLGPROC)MainMenu::DlgProc);
}