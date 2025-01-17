#include "pch.h"
#include "CSSHScene.h"

#include "CPlayer_SSH_Fire.h"
#include "CPlayer_SSH_Ice.h"

#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CAbstractFactory.h"

CSSHScene::CSSHScene() : m_bChange(false)
{
}

CSSHScene::~CSSHScene()
{
}

void CSSHScene::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SSH_Ice>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SSH_Fire>::Create());
	// ������ �� Ÿ������ ����
	CObjMgr::Get_Instance()->Get_Player()->Set_Target(CObjMgr::Get_Instance()->Get_LastPlayer());
	// ���� ������ Ÿ������ ����
	CObjMgr::Get_Instance()->Get_LastPlayer()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
}

int CSSHScene::Update()
{
	Key_Input();
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CSSHScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Update();
}

void CSSHScene::Render(HDC hDC)
{
	Ellipse(hDC,
		int(SSH_FIRE->Get_Info().vPos.x - 100.f),
		int(SSH_FIRE->Get_Info().vPos.y - 100.f),
		int(SSH_FIRE->Get_Info().vPos.x + 100.f),
		int(SSH_FIRE->Get_Info().vPos.y + 100.f));

	Ellipse(hDC,
		int(SSH_ICE->Get_Info().vPos.x - 100.f),
		int(SSH_ICE->Get_Info().vPos.y - 100.f),
		int(SSH_ICE->Get_Info().vPos.x + 100.f),
		int(SSH_ICE->Get_Info().vPos.y + 100.f));

	CObjMgr::Get_Instance()->Render(hDC);
}

void CSSHScene::Release()
{
	CObjMgr::Get_Instance()->Release();
}

void CSSHScene::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bChange = !m_bChange; // ������ bChange�� �ݵ�� �ݴ뿩�� �� ( ���� �� ���� ȸ�� )
		SSH_FIRE->Set_bChange(!m_bChange);
		SSH_ICE->Set_bChange(m_bChange);
	}
}
