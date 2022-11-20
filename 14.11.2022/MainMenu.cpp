#include "MainMenu.h"
#include "AutoMenu.h"
#include "KafeMenu.h"

BOOL MainMenu::OnInit(HWND hWnd, HWND Focus, LPARAM lParam)
{
	hButtAuto = GetDlgItem(hWnd, IDC_BUTT_AUTO);
	hButtKafe = GetDlgItem(hWnd, IDC_BUTT_KAFE);
	hButtEnd = GetDlgItem(hWnd, IDC_BUTT_END);
	hCostAuto = GetDlgItem(hWnd, IDC_STAT_AUTO);
	hCostKafe = GetDlgItem(hWnd, IDC_STAT_KAFE);
	hCostEnd = GetDlgItem(hWnd, IDC_STAT_END);
	return TRUE;
}

VOID MainMenu::OnCommand(HWND hWnd, int id, HWND, UINT)
{
	switch (id)
	{
	case IDC_BUTT_AUTO:
	{
		int res = DialogBox(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(AutoMenu::DialogID),
			hWnd,
			(DLGPROC)AutoMenu::DlgProc
		);

		wsprintfW(buff, TEXT("%i.%i"), res / MIN_ACCURACY, res - res / MIN_ACCURACY * MIN_ACCURACY);
		SetWindowText(hCostAuto, buff);

		CalcRes();
	} break;

	case IDC_BUTT_KAFE:
	{
		int res = DialogBox(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(KafeMenu::DialogID),
			hWnd,
			(DLGPROC)KafeMenu::DlgProc
		);

		wsprintfW(buff, TEXT("%i.%i"), res / MIN_ACCURACY, res - res / MIN_ACCURACY * MIN_ACCURACY);
		SetWindowText(hCostKafe, buff);

		CalcRes();
	} break;

	case IDC_BUTT_END:
	{
		GetWindowText(hCostEnd, buff, DEFAULT_SIZE_STR);
		EndDialog(hWnd, _wtof(buff) * MIN_ACCURACY);

		const WCHAR* EndText = TEXT("Заказ оформлен.\nК оплате: %f");
		swprintf(buff, M_COST_STR_LEN + _tcslen(EndText) - 2, EndText, _wtof(buff));
		MessageBox(hWnd, buff, TEXT("Оплата"), MB_OK | MB_ICONINFORMATION);
	}break;
	}
}

VOID MainMenu::OnClose(HWND hWnd)
{
	EndDialog(hWnd, NULL);
}

void MainMenu::CalcRes()
{
	double res = 0;
	GetWindowText(hCostAuto, buff, DEFAULT_SIZE_STR);
	res += _wtof(buff);
	GetWindowText(hCostKafe, buff, DEFAULT_SIZE_STR);
	res += _wtof(buff);

	swprintf(buff, M_COST_STR_LEN, TEXT("%f"), res);
	SetWindowText(hCostEnd, buff);
}

MainMenu& MainMenu::inst()
{
	static MainMenu rez;
	return rez;
}

BOOL MainMenu::DlgProc(HWND hWnd, UINT mess, WPARAM wParam, LPARAM lParam)
{
	switch (mess)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, inst().OnInit);
		HANDLE_MSG(hWnd, WM_CLOSE, inst().OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, inst().OnCommand);
	}

	return FALSE;
}
