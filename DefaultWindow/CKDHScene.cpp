#include "pch.h"
#include "CKDHScene.h"
#include "CKDHPlayer.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CKDHScene::CKDHScene()
{
}

CKDHScene::~CKDHScene()
{
	Release();
}

void CKDHScene::Initialize()
{
	CObj* player = CAbstractFactory<CKDHPlayer>::Create();
	CObj* pad = CAbstractFactory<CHexaPad>::Create();
	static_cast<CHexaPad*>(pad)->SetPlayer(static_cast<CKDHPlayer*>(player));
	static_cast<CHexaPad*>(pad)->SetDirection(1);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, player);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pad);
}

int CKDHScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	
	return 0;
}

void CKDHScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CKDHScene::Render(HDC hDC)
{
	Rectangle(hDC,
		0,
		0,
		WINCX,
		WINCY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CKDHScene::Release()
{
	//CObjMgr::Get_Instance()->Release();
}
