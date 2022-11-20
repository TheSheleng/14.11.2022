#pragma once
#include "Header.h"

class MainMenu
{
	MainMenu() = default;
	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;

	WCHAR buff[DEFAULT_SIZE_STR];

	HWND hButtAuto, hButtKafe, hButtEnd,
		 hCostAuto, hCostKafe, hCostEnd;

	BOOL OnInit(HWND, HWND, LPARAM);
	VOID OnCommand(HWND, int, HWND,UINT);
	VOID OnClose(HWND);

	void CalcRes();
public:
	static const int DialogID = IDD_DIALOG1;
	static MainMenu& inst();
	static BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
};