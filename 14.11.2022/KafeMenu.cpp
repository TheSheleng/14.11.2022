#include "KafeMenu.h"

BOOL KafeMenu::OnInit(HWND hWnd, HWND Focus, LPARAM lParam)
{
	for (int i = 0; i < szMenu; ++i)
	{
		hEdit[i] = GetDlgItem(hWnd, i + IDC_EDIT1);
		hStat[i] = GetDlgItem(hWnd, i + IDC_STAT1);
	}

	hCostEnd = GetDlgItem(hWnd, IDC_COST_END);
	hButtEnd = GetDlgItem(hWnd, IDC_BUTT_END);

	return TRUE;
}

VOID KafeMenu::OnCommand(HWND hWnd, int id, HWND Ctl, UINT Notify)
{
	if (id >= IDC_EDIT1 && id <= IDC_EDIT1 + szMenu  - 1 && Notify == EN_UPDATE)
	{
		double test = 0;

		for (int i = 0; i < szMenu; ++i)
		{
			GetWindowText(hEdit[i], buff, DEFAULT_SIZE_STR);
			double res = _wtof(buff);
			GetWindowText(hStat[i], buff, DEFAULT_SIZE_STR);
			test += res * _wtof(buff);
		}

		swprintf(buff, M_COST_STR_LEN, TEXT("%f"), test);
		SetWindowText(hCostEnd, buff);
	}

	if (id == IDC_BUTT_END)
	{
		GetWindowText(hCostEnd, buff, DEFAULT_SIZE_STR);
		EndDialog(hWnd, _wtof(buff) * MIN_ACCURACY);
	}
}

VOID KafeMenu::OnClose(HWND hWnd)
{
	EndDialog(hWnd, NULL);
}

KafeMenu& KafeMenu::inst()
{
	static KafeMenu rez;
	return rez;
}

BOOL KafeMenu::DlgProc(HWND hWnd, UINT mess, WPARAM wParam, LPARAM lParam)
{
	switch (mess)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, inst().OnInit);
		HANDLE_MSG(hWnd, WM_CLOSE, inst().OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, inst().OnCommand);
	}

	return FALSE;
}
