#include "pch.h"
#include "CThorn.h"

CThorn::CThorn()
{
}

CThorn::~CThorn()
{
	Release();
}

void CThorn::Initialize()
{
	m_tInfo.vPos = { 590.f, 200.f, 0.f };
	m_fSpeed = 2.f;

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fAngle = 70.f;

	points[0] = { 0.f,		-10.154f,		0.f };
	points[1] = { 10.f,	 5.77f,		0.f };
	points[2] = { -10.f,	 5.77f,		0.f };

	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

int CThorn::Update()
{
	D3DXMATRIX		matRotZ, matTrans1, matTrans2, matScale;


	D3DXMatrixScaling(&matScale, 2.f, 2.f, 2.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans2, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);


	m_tInfo.matWorld = matScale * matRotZ * matTrans2;

	//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &m_tInfo.matWorld);

	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformCoord(&transformVertex[i], &points[i], &m_tInfo.matWorld);
	}

	return 0;
}


void CThorn::Late_Update()
{
}

void CThorn::Render(HDC hDC)
{
	MoveToEx(hDC, (int)transformVertex[0].x, (int)transformVertex[0].y, nullptr);
	LineTo(hDC, (int)transformVertex[1].x, (int)transformVertex[1].y);
	LineTo(hDC, (int)transformVertex[2].x, (int)transformVertex[2].y);
	LineTo(hDC, (int)transformVertex[0].x, (int)transformVertex[0].y);


	Ellipse(hDC, (int)transformVertex[0].x - 5, (int)transformVertex[0].y - 5, (int)transformVertex[0].x + 5, (int)transformVertex[0].y + 5);

	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("x : %f  \t y : % f"), transformVertex[1].x, transformVertex[1].y);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 350, 50, szBuffer3, (int)_tcslen(szBuffer3));
}

void CThorn::Release()
{
}

