#include "pch.h"
#include "CMenu.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

void CMenu::Initialize()
{
}

int CMenu::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MOO);
		return 0;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_SSH);
		return 0;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_HERO);
		return 0;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_KDH);
		return 0;
	}
	return 0;
}

void CMenu::Late_Update()
{
}

void CMenu::Render(HDC hDC)
{
	TCHAR szBuffer1[128];
	_stprintf_s(szBuffer1, _T("1. Orbit or bit"));
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 300, 150, szBuffer1, (int)_tcslen(szBuffer1));

	TCHAR szBuffer2[128];
	_stprintf_s(szBuffer2, _T("2. Super Hexagon"));
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 300, 250, szBuffer2, (int)_tcslen(szBuffer2));

	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("3. A Dance of Fire and Ice"));
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 300, 350, szBuffer3, (int)_tcslen(szBuffer3));

	TCHAR szBuffer4[128];
	_stprintf_s(szBuffer4, _T("4.Rhythm Paradise"));
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 300, 450, szBuffer4, (int)_tcslen(szBuffer4));

}

void CMenu::Release()
{
	
}
