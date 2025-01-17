#include "pch.h"
#include "COrbit_or_bit.h"
#include "CPlayer_moo.h"
#include "COrbit.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CThorn.h"

COrbit_or_bit::COrbit_or_bit() : m_pPlayer(nullptr), m_pOrbit(nullptr)
{
}

COrbit_or_bit::~COrbit_or_bit()
{
}

void COrbit_or_bit::Initialize()
{

	//CSoundMgr::Get_Instance()->Initialize();
	//CSoundMgr::Get_Instance()->PlayEvent("event:/Tobu & Itro - Sunburst");
	//CSoundMgr::Get_Instance()->Update();
	

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_moo>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CThorn>::Create(100.f, 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<COrbit>::Create());
}

int COrbit_or_bit::Update()
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void COrbit_or_bit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void COrbit_or_bit::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void COrbit_or_bit::Release()
{
	CObjMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->Release();
}
