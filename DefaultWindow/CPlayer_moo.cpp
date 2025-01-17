#include "pch.h"
#include "CPlayer_moo.h"
#include "CSoundMgr.h"
#include "CKeyMgr.h"

CPlayer_moo::CPlayer_moo() : m_Diagonal(0)
{
}

CPlayer_moo::~CPlayer_moo()
{
	Release();
}

void CPlayer_moo::Initialize()
{
	m_tInfo.vPos = { 153.f, 153.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_fSpeed = 0.5f;

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

	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans2, 400.f , 300.f, 0.f);

	m_tInfo.matWorld =  matRotZ * matTrans2;

	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);

	return 0;
}
void CPlayer_moo::Late_Update()
{
}

void CPlayer_moo::Render(HDC hDC)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Ellipse(hDC,
		int(m_tInfo.vPos.x - 15.f),
		int(m_tInfo.vPos.y - 15.f),
		int(m_tInfo.vPos.x + 15.f),
		int(m_tInfo.vPos.y + 15.f));

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("x : %f \t y : %f"), m_tInfo.vPos.x, m_tInfo.vPos.y);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, m_tInfo.vPos.x - 100, m_tInfo.vPos.y + 20, szBuffer3, (int)_tcslen(szBuffer3));
}

void CPlayer_moo::Release()
{
}

void CPlayer_moo::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
	{
		m_vOriginPoint = { 153.f, 153.f, 0.f };
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
	{
		m_vOriginPoint = { 128.f, 128.f, 0.f };
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
	{
		m_vOriginPoint = { 153.f, 153.f, 0.f };
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		m_vOriginPoint = { 128.f, 128.f, 0.f };
	}
}

