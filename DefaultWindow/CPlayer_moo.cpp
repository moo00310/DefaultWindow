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
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_fSpeed = 1.5f;
	m_fAngle = 0.f;

	m_Diagonal = 220.f;

	m_eRender = RENDER_GAMEOBJECT;
}

int CPlayer_moo::Update()
{
	Key_Input();

	if (m_fAngle >= 360)
		m_fAngle = 0;
	else
		m_fAngle += m_fSpeed;

	m_tInfo.vPos.x = m_Diagonal * cosf(m_fAngle * PI / 180) + 400;
	m_tInfo.vPos.y = m_Diagonal * sinf(m_fAngle * PI / 180) + 300;

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
		m_Diagonal = 220.f;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_Diagonal = 180.f;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_Diagonal = 220.f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_Diagonal = 180.f;
	}
}

