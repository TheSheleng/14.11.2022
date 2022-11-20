#pragma once
#include "Header.h"

class AutoMenu
{
	AutoMenu() = default;
	AutoMenu(const AutoMenu&) = delete;
	AutoMenu& operator=(const AutoMenu&) = delete;

	WCHAR buff[DEFAULT_SIZE_STR];

	static const int ENTER_LIM_CHAR = 3;

	HWND hMarkaName, hMarkaCost,
		 hEnterVol, hEnterSum, hAmVol, hAmSum,
		 hCostEnd, hButtEnd;

	BOOL OnInit(HWND, HWND, LPARAM);
	void OnCommand(HWND, int, HWND, UINT);
	void OnClose(HWND);

	double GetMarkaCost();

	void FixByVol();
	void FixBySum();

public:
	static const int DialogID = IDD_DIALOG2;
	static AutoMenu& inst();
	static BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
};