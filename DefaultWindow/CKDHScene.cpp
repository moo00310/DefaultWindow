#include "pch.h"
#include "CKDHScene.h"
#include "CKDHPlayer.h"

CKDHScene::CKDHScene() : m_Player(nullptr), m_Pad(nullptr)
{
}

CKDHScene::~CKDHScene()
{
	Release();
}

void CKDHScene::Initialize()
{
	m_Player = new CKDHPlayer();
	m_Pad = new CHexaPad(m_Player, 3);

	m_Pad->Initialize();
	m_Player->Initialize();
}

int CKDHScene::Update()
{
	m_Pad->Update();
	m_Player->Update();
	
	return 0;
}

void CKDHScene::Late_Update()
{
	m_Pad->Late_Update();
	m_Player->Late_Update();
}

void CKDHScene::Render(HDC hDC)
{
	Rectangle(hDC,
		0,
		0,
		WINCX,
		WINCY);

	m_Pad->Render(hDC);
	m_Player->Render(hDC);
}

void CKDHScene::Release()
{
	m_Pad->Release();
	m_Player->Release();

	Safe_Delete<CKDHPlayer*>(m_Player);
	Safe_Delete<CHexaPad*>(m_Pad);
}
