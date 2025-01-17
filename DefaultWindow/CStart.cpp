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
}

void CStart::Release()
{
}
