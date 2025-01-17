#include "pch.h"
#include "COrbit_or_bit.h"
#include "CPlayer_moo.h"
#include "COrbit.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CThorn.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"

COrbit_or_bit::COrbit_or_bit() : m_pPlayer(nullptr), m_pOrbit(nullptr)
{
}

COrbit_or_bit::~COrbit_or_bit()
{
	Release();
}

void COrbit_or_bit::Initialize()
{

	//CSoundMgr::Get_Instance()->Initialize();
	//CSoundMgr::Get_Instance()->PlayEvent("event:/Tobu & Itro - Sunburst");
	//CSoundMgr::Get_Instance()->Update();
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_moo>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<COrbit>::Create());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CThorn>::Create(220.f, 260.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CThorn>::Create(180.f, 300.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CThorn>::Create(120.f, 260.f));


	// 카메라 플레이어 추적
	CCameraMgr::Get_Instance()->Initailize();
}

int COrbit_or_bit::Update()
{
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		CCameraMgr::Get_Instance()->Is_Reverce(true);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{
		CCameraMgr::Get_Instance()->Is_Reverce(false);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		CCameraMgr::Get_Instance()->Set_State(CS_Shake1);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		CCameraMgr::Get_Instance()->Set_State(CS_END);
	}

	return 0;
}

void COrbit_or_bit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	bool isCol = CObjMgr::Get_Instance()->Collision_Check();
}

void COrbit_or_bit::Render(HDC hDC)
{
	if (CKeyMgr::Get_Instance()->GetKeyState(VK_RIGHT) ||
		CKeyMgr::Get_Instance()->GetKeyState(VK_UP))
	{
		RECT rect = { 0, 0, WINCX, WINCY };
		HBRUSH hBrush = CreateSolidBrush(RGB(211, 211, 211));
		FillRect(hDC, &rect, hBrush);
		DeleteObject(hBrush);
	}
	
	CObjMgr::Get_Instance()->Render(hDC);
}

void COrbit_or_bit::Release()
{
	CObjMgr::Get_Instance()->Release();
}
