#pragma once
#include "Header.h"

class KafeMenu
{
	KafeMenu() = default;
	KafeMenu(const KafeMenu&) = delete;
	KafeMenu& operator=(const KafeMenu&) = delete;

	WCHAR buff[DEFAULT_SIZE_STR];

	static const size_t szMenu = 7;
	HWND hEdit[szMenu], hStat[szMenu],
		hCostEnd, hButtEnd;

	BOOL OnInit(HWND, HWND, LPARAM);
	VOID OnCommand(HWND, int, HWND, UINT);
	VOID OnClose(HWND);

public:
	static const int DialogID = IDD_DIALOG3;
	static KafeMenu& inst();
	static BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
};