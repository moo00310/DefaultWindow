#include "pch.h"
#include "CKDHScene.h"
#include "CKDHPlayer.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CHexaPadManager.h"

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
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, player);

	CreatePattern();
}

int CKDHScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	CHexaPadManager::Get_Instance()->OnPattern();
	
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
	CHexaPadManager::Get_Instance()->Destroy_Instance();
}

void CKDHScene::CreatePattern()
{
	CSequence sequence;
	sequence.sequence = [&]()
		{
			CObj* pad1 = CAbstractFactory<CHexaPad>::Create();
			static_cast<CHexaPad*>(pad1)->SetDirection(DIR_DOWN);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pad1);

			CObj* pad2 = CAbstractFactory<CHexaPad>::Create();
			static_cast<CHexaPad*>(pad2)->SetDirection(DIR_UP);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pad2);
		};
	sequence.fCount = 1.f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			CObj* pad1 = CAbstractFactory<CHexaPad>::Create();
			static_cast<CHexaPad*>(pad1)->SetDirection(DIR_LEFT);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pad1);

			CObj* pad2 = CAbstractFactory<CHexaPad>::Create();
			static_cast<CHexaPad*>(pad2)->SetDirection(DIR_RIGHT);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pad2);
		};
	sequence.fCount = 1.f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);
}
