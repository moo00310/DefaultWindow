#include "pch.h"
#include "CStart.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"

void CStart::Initialize()
{
}

int CStart::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
		return 0;
	}
	return 0;
}

void CStart::Late_Update()
{
}

void CStart::Render(HDC hDC)
{
	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("Team_2 Rhythm_Game"));
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 300, 200, szBuffer3, (int)_tcslen(szBuffer3));
}

void CStart::Release()
{
}
