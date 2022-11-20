#include "AutoMenu.h"

BOOL AutoMenu::OnInit(HWND hWnd, HWND Focus, LPARAM lParam)
{
	hMarkaName = GetDlgItem(hWnd, IDC_MARK_NAME);
	hMarkaCost = GetDlgItem(hWnd, IDC_MARK_COST);
	hEnterVol = GetDlgItem(hWnd, IDC_ENTER_VOL);
	hEnterSum = GetDlgItem(hWnd, IDC_ENTER_SUM);
	hAmVol = GetDlgItem(hWnd, IDC_AM_VOL); 
	hAmSum = GetDlgItem(hWnd, IDC_AM_SUM);
	hCostEnd = GetDlgItem(hWnd, IDC_COST_END);
	hButtEnd = GetDlgItem(hWnd, IDC_BUTT_END);

	const std::pair<const WCHAR*, int> mCost[] = {
		{ TEXT("A-92"), 4875 },
		{ TEXT("A-95"), 4917 },
		{ TEXT("A-95 Prem"), 5021 },
		{ TEXT("Diesel"), 5419 },
		{ TEXT("Gas"), 2849 },
	};

	for (const std::pair<const WCHAR*, int> i : mCost)
		SendMessage(hMarkaName, CB_SETITEMDATA, 
			SendMessage(hMarkaName, 
				CB_ADDSTRING, 0, 
				LPARAM(i.first)
			), i.second);

	SendMessage(hMarkaName, CB_SETCURSEL, 0, 0); 
	swprintf(buff, M_COST_STR_LEN, TEXT("%f"), GetMarkaCost());
	SetWindowText(hMarkaCost, buff);
	SendMessage(hAmVol, BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(hEnterVol, EM_SETLIMITTEXT, ENTER_LIM_CHAR, 0);
	SendMessage(hEnterSum, EM_SETLIMITTEXT, ENTER_LIM_CHAR, 0);

	SetWindowText(hEnterVol, TEXT("0"));
	SetWindowText(hEnterSum, TEXT("0"));

	return TRUE;
}

void AutoMenu::OnCommand(HWND hWnd, int id, HWND Ctl, UINT Notify)
{
	switch (id)
	{
	case IDC_BUTT_END: 
	{
		GetWindowText(hCostEnd, buff, DEFAULT_SIZE_STR);
		EndDialog(hWnd, _wtof(buff) * MIN_ACCURACY);
	} break;

	case IDC_MARK_NAME:
	{
		if (Notify == CBN_SELCHANGE)
		{
			swprintf(buff, M_COST_STR_LEN, TEXT("%f"), GetMarkaCost());
			SetWindowText(hMarkaCost, buff);

			FixByVol();
			FixBySum();
		}
	}break;

	case IDC_ENTER_VOL:
	{
		if (Notify == EN_UPDATE) FixByVol();
	}break;

	case IDC_ENTER_SUM:
	{
		if (Notify == EN_UPDATE) FixBySum();
	}break;

	case IDC_AM_VOL:
	{
		SendMessage(hEnterVol, EM_SETREADONLY, FALSE, 0);
		SendMessage(hEnterSum, EM_SETREADONLY, TRUE, 0);
	} break;

	case IDC_AM_SUM:
	{
		SendMessage(hEnterVol, EM_SETREADONLY, TRUE, 0);
		SendMessage(hEnterSum, EM_SETREADONLY, FALSE, 0);
	} break;
	}
}

void AutoMenu::OnClose(HWND hWnd)
{
	EndDialog(hWnd, NULL);
}

double AutoMenu::GetMarkaCost()
{
	return SendMessage(hMarkaName, CB_GETITEMDATA,
			   SendMessage(hMarkaName, CB_GETCURSEL, 0, 0), 0
		   ) / (double)MIN_ACCURACY;
}

void AutoMenu::FixByVol()
{
	if (SendMessage(hAmVol, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		GetWindowText(hEnterVol, buff, DEFAULT_SIZE_STR);
		swprintf(buff, M_COST_STR_LEN, TEXT("%f"), _wtof(buff) * GetMarkaCost());
		SetWindowText(hEnterSum, buff);
		SetWindowText(hCostEnd, buff);
	}
}

void AutoMenu::FixBySum()
{
	if (SendMessage(hAmSum, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		GetWindowText(hEnterSum, buff, DEFAULT_SIZE_STR);
		SetWindowText(hCostEnd, buff);
		swprintf(buff, M_COST_STR_LEN, TEXT("%f"), _wtof(buff) / GetMarkaCost());
		SetWindowText(hEnterVol, buff);
	}
}

AutoMenu& AutoMenu::inst()
{
	static AutoMenu rez;
	return rez;
}

BOOL AutoMenu::DlgProc(HWND hWnd, UINT mess, WPARAM wParam, LPARAM lParam)
{
	switch (mess)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, inst().OnInit);
		HANDLE_MSG(hWnd, WM_CLOSE, inst().OnClose);
		HANDLE_MSG(hWnd, WM_COMMAND, inst().OnCommand);
	}
	return	FALSE;
}
