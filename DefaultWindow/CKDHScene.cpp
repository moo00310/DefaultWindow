#include "pch.h"
#include "CKDHScene.h"
#include "CKDHPlayer.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CHexaPadManager.h"
#include "CSoundMgr.h"

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

	CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlayEvent("event:/Milkyway");
	CSoundMgr::Get_Instance()->Update();
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
	CHexaPadManager::Get_Instance()->ClearPattern();
	CHexaPadManager::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
}

void CKDHScene::CreatePattern()
{
	CSequence sequence;
	sequence.sequence = [&]()
		{
		};
	sequence.fCount = 1.5f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_DOWN);
			AddPad(DIR_UP);
		};
	sequence.fCount = 0.5f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_LEFT);
			AddPad(DIR_RIGHT);
		};
	sequence.fCount = 0.8f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_DOWN);
			AddPad(DIR_UP);
		};
	sequence.fCount = 0.5f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_LEFT);
			AddPad(DIR_RIGHT);
		};
	sequence.fCount = 0.8f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_DOWN);
			AddPad(DIR_UP);
		};
	sequence.fCount = 0.5f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_LEFT);
			AddPad(DIR_RIGHT);
		};
	sequence.fCount = 0.8f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_UP);
			AddPad(DIR_RIGHT);
		};
	sequence.fCount = 0.4f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_UP);
			AddPad(DIR_RIGHT);
			AddPad(DIR_DOWN);
		};
	sequence.fCount = 0.4f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);

	sequence.sequence = [&]()
		{
			AddPad(DIR_UP);
			AddPad(DIR_RIGHT);
			AddPad(DIR_DOWN);
			AddPad(DIR_LEFT);
		};
	sequence.fCount = 1.3f;

	CHexaPadManager::Get_Instance()->AddPattern(sequence);
}

void CKDHScene::AddPad(kDIRECTION _direction)
{
	CObj* pad = CAbstractFactory<CHexaPad>::Create();
	static_cast<CHexaPad*>(pad)->SetDirection(_direction);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pad);
}
