#include "pch.h"
#include "CPlayer_moo.h"
#include "CSoundMgr.h"

CPlayer_moo::CPlayer_moo() : m_Diagonal(0)
{
}

CPlayer_moo::~CPlayer_moo()
{
	Release();
}

void CPlayer_moo::Initialize()
{
	m_tInfo.vPos = { 155.f, 155.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_fSpeed = 1.5f;

	m_Diagonal = 220.f;

	m_vOriginPoint = m_tInfo.vPos;

	m_eRender = RENDER_GAMEOBJECT;
}

int CPlayer_moo::Update()
{
	Key_Input();

	if (m_fAngle >= 360) m_fAngle = 0;
	else m_fAngle += m_fSpeed;

	m_tInfo.vPos = m_vOriginPoint; // °ª ÁßÃ¸ ¹æÁö
	D3DXMATRIX	matRotZ, matTrans1, matTrans2, matScale;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans2, 400.f, 300.f, 0.f);

	m_tInfo.matWorld =  matRotZ * matTrans2;

	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);

	return 0;
}
void CPlayer_moo::Late_Update()
{
}

void CPlayer_moo::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 20.f),
		int(m_tInfo.vPos.y - 20.f),
		int(m_tInfo.vPos.x + 20.f),
		int(m_tInfo.vPos.y + 20.f));
}

void CPlayer_moo::Release()
{
}

void CPlayer_moo::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_vOriginPoint = { 155.f, 155.f, 0.f };
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_vOriginPoint = { 125.f, 125.f, 0.f };
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_vOriginPoint = { 155.f, 155.f, 0.f };
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_vOriginPoint = { 125.f, 125.f, 0.f };
	}
}

