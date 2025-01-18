#include "pch.h"
#include "CSSHScene.h"

#include "CPlayer_SSH_Fire.h"
#include "CPlayer_SSH_Ice.h"
#include "CBlock_SSH.h"

#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CAbstractFactory.h"

CSSHScene::CSSHScene() 
	: m_bChange(false), m_fCheckAngle(0.f), m_fMaxAngle(190.f),
	m_iBlockCount(0), m_iBlockSaveCount(0)
{
}

CSSHScene::~CSSHScene()
{
	Release();
}

void CSSHScene::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SSH_Ice>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SSH_Fire>::Create());
	// 얼음이 불 타깃으로 잡음
	CObjMgr::Get_Instance()->Get_Player()->Set_Target(CObjMgr::Get_Instance()->Get_LastPlayer());
	// 불이 얼음을 타깃으로 잡음
	CObjMgr::Get_Instance()->Get_LastPlayer()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	for (int i = 0; i < 5; i++)
	{
		CObjMgr::Get_Instance()->
			Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock_SSH>::Create({ 25.f + i * 50.f, 300.f, 0.f}));
	}

	CObjMgr::Get_Instance()->
		Add_Object(OBJ_BLOCK, CAbstractFactory<CBlock_SSH>::Create({ 225.f, 350.f, 0.f }, 90.f));
}

int CSSHScene::Update()
{
	Key_Input();
	CObjMgr::Get_Instance()->Update();

	if (!m_bChange) // 불이 공전
	{
		for (auto& iter : CObjMgr::Get_Instance()->Get_ObjList()[OBJ_BLOCK])
		{
			if (m_iBlockSaveCount < m_iBlockCount)
			{
				m_iBlockSaveCount = m_iBlockCount;
				break;
			}

			if (iter->Get_Angle() <= SSH_FIRE->Get_Angle())
			{
				SSH_FIRE->Set_Angle(iter->Get_Angle());
				m_bChange = !m_bChange;
				SSH_FIRE->Set_bRev(!m_bChange);
				SSH_ICE->Set_bRev(m_bChange);
				++m_iBlockCount;

				if (iter->Get_Angle() <= SSH_ICE->Get_Angle())
				{
					SSH_ICE->Set_Angle(0.f);
				}
			}
		}

	}
	else if (m_bChange) // 얼음이 공전
	{
		for (auto& iter : CObjMgr::Get_Instance()->Get_ObjList()[OBJ_BLOCK])
		{
			if (iter->Get_Angle() <= SSH_ICE->Get_Angle())
			{
				SSH_ICE->Set_Angle(iter->Get_Angle());
				m_bChange = !m_bChange;
				SSH_FIRE->Set_bRev(!m_bChange);
				SSH_ICE->Set_bRev(m_bChange);
				++m_iBlockCount;

				if (iter->Get_Angle() <= SSH_FIRE->Get_Angle())
				{
					SSH_FIRE->Set_Angle(0.f);
				}
			}
		}
	}

	return 0;
}

void CSSHScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Update();
}

void CSSHScene::Render(HDC hDC)
{
	//Ellipse(hDC,
	//	int(SSH_FIRE->Get_Info().vPos.x - 100.f),
	//	int(SSH_FIRE->Get_Info().vPos.y - 100.f),
	//	int(SSH_FIRE->Get_Info().vPos.x + 100.f),
	//	int(SSH_FIRE->Get_Info().vPos.y + 100.f));

	//Ellipse(hDC,
	//	int(SSH_ICE->Get_Info().vPos.x - 100.f),
	//	int(SSH_ICE->Get_Info().vPos.y - 100.f),
	//	int(SSH_ICE->Get_Info().vPos.x + 100.f),
	//	int(SSH_ICE->Get_Info().vPos.y + 100.f));

	CObjMgr::Get_Instance()->Render(hDC);

	TCHAR szAngle[100]{};

	swprintf_s(szAngle, L"현재 각도 : %.2f", m_fCheckAngle);
	TextOut(hDC, 30, 20, szAngle, lstrlen(szAngle));
}

void CSSHScene::Release()
{
	CObjMgr::Get_Instance()->Release();
}

void CSSHScene::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		//m_bChange = !m_bChange; // 각자의 bChange는 반드시 반대여야 함 ( 같을 시 같이 회전 )
		//SSH_FIRE->Set_bRev(!m_bChange);
		//SSH_ICE->Set_bRev(m_bChange);

		//if (!m_bChange)
		//{
		//	if (180 < SSH_ICE->Get_Angle())
		//	{
		//		SSH_FIRE->Set_Angle(SSH_ICE->Get_Angle() - 180.f);
		//	}
		//	else
		//		SSH_FIRE->Set_Angle(SSH_ICE->Get_Angle() + 180.f);
		//}
		//else
		//{
		//	if (180 < SSH_FIRE->Get_Angle())
		//	{
		//		SSH_ICE->Set_Angle(SSH_FIRE->Get_Angle() - 180.f);
		//	}
		//	else
		//		SSH_ICE->Set_Angle(SSH_FIRE->Get_Angle() + 180.f);
		//}

		//if(m_fCheckAngle )
	}
}
