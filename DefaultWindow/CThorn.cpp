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
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_vMidPoint = { 400.f, 300.f, 0.f };

	m_vPoints[0] = { 0.f,		-10.154f,	0.f };
	m_vPoints[1] = { 10.f,		5.77f,		0.f };
	m_vPoints[2] = { -10.f,		5.77f,		0.f };

	m_fSpeed = 2.f;
	m_fAngle = TranceAngle();
	m_eRender = RENDER_GAMEOBJECT;
}

int CThorn::Update()
{
	D3DXMATRIX		matRotZ, matTrans1, matTrans2, matScale;

	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.5f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans2, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans2;

	for (int i = 0; i < 3; i++)
	{
		D3DXVec3TransformCoord(&m_vTransformVertex[i], &m_vPoints[i], &m_tInfo.matWorld);
	}

	return 0;
}


void CThorn::Late_Update()
{
}

void CThorn::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vTransformVertex[0].x, (int)m_vTransformVertex[0].y, nullptr);
	LineTo(hDC, (int)m_vTransformVertex[1].x, (int)m_vTransformVertex[1].y);
	LineTo(hDC, (int)m_vTransformVertex[2].x, (int)m_vTransformVertex[2].y);
	LineTo(hDC, (int)m_vTransformVertex[0].x, (int)m_vTransformVertex[0].y);


	Ellipse(hDC, (int)m_vTransformVertex[0].x - 5, (int)m_vTransformVertex[0].y - 5, (int)m_vTransformVertex[0].x + 5, (int)m_vTransformVertex[0].y + 5);
}

void CThorn::Release()
{
}


float CThorn::TranceAngle()
{
	D3DXVECTOR3 temp = m_tInfo.vPos - m_vMidPoint;
	D3DXVec3Normalize(&m_tInfo.vDir, &temp);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	float angle = acosf(fDot);

	 if (m_tInfo.vPos.x < m_vMidPoint.x)
		 angle = 2 *PI - angle;

	 return angle;
}

