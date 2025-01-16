#include "pch.h"
#include "COrbit.h"
#include "CSoundMgr.h"

COrbit::COrbit()
{
}

COrbit::~COrbit()
{
}

void COrbit::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_fSpeed = 10.f;

    m_eRender = RENDER_BACKGROUND;
}

int COrbit::Update()
{
    return 0;
}

void COrbit::Late_Update()
{
}


void COrbit::Render(HDC hDC)
{

    HPEN hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0)); 
    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

    // 타원 그리기
    Ellipse(hDC,
        int(m_tInfo.vPos.x - 200.f),
        int(m_tInfo.vPos.y - 200.f),
        int(m_tInfo.vPos.x + 200.f),
        int(m_tInfo.vPos.y + 200.f));

    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);
}

void COrbit::Release()
{
}

