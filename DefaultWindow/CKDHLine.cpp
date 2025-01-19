#include "pch.h"
#include "CKDHLine.h"
#include "CObjMgr.h"
#include "CKDHScene.h"

CKDHLine::CKDHLine()
{
	ZeroMemory(&m_ResetPosition, sizeof(D3DXVECTOR3));
	m_Player = static_cast<CKDHPlayer*>(CObjMgr::Get_Instance()->Get_Player());
}

CKDHLine::~CKDHLine()
{
	Release();
}

void CKDHLine::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_fScale = 600.f;

	m_localPosition = { 0.f, 0.f, 0.f };
	m_localScale = { 1.f, 1.f, 0.f };

	vertex[0].x = m_localPosition.x;
	vertex[0].y = m_localPosition.y;

	vertex[1].x = m_localPosition.x + m_fScale;
	vertex[1].y = m_localPosition.y;

	for (int i = 0; i < 2; i++)
	{
		vertexOrigin[i].x = vertex[i].x;
		vertexOrigin[i].y = vertex[i].y;
	}

	D3DXMatrixIdentity(&m_MatrixPosition);
	D3DXMatrixIdentity(&m_MatrixRotate);
	D3DXMatrixIdentity(&m_MatrixScale);
	D3DXMatrixIdentity(&m_MatrixRevolution);
	D3DXMatrixIdentity(&m_MatrixParent);
	D3DXMatrixIdentity(&m_MatrixWorld);

	m_revolAngle = 0.f;
	m_revOriginAngle = 0.f;
	m_rotAngle = 0.f;
}

int CKDHLine::Update()
{
	return 0;
}

void CKDHLine::Late_Update()
{
	m_revolAngle = g_RevolAngle + m_revOriginAngle;

	vertexOrigin[0].x = m_ResetPosition.x;
	vertexOrigin[0].y = m_ResetPosition.y;

	vertexOrigin[1].x = m_ResetPosition.x + m_fScale;
	vertexOrigin[1].y = m_ResetPosition.y;

	// 크기 행렬.
	D3DXMatrixScaling(&m_MatrixScale, m_localScale.x, m_localScale.y, m_localScale.z);

	// 회전 행렬.
	D3DXMatrixRotationZ(&m_MatrixRotate, D3DXToRadian(m_rotAngle));

	// 이동 행렬.
	D3DXMatrixTranslation(&m_MatrixPosition, m_localPosition.x, m_localPosition.y, m_localPosition.z);

	// 공전 행렬.
	D3DXMatrixRotationZ(&m_MatrixRevolution, D3DXToRadian(m_revolAngle));

	// 부모 행렬.
	D3DXMatrixTranslation(&m_MatrixParent, m_Player->GetLocalParentPosition().x, m_Player->GetLocalParentPosition().y, m_Player->GetLocalParentPosition().z);

	// 월드 좌표로 변환.
	// 월드 행렬 = 크기 * 자전(회전) * 이동 * 공전 * 부모
	m_MatrixWorld = m_MatrixScale * m_MatrixRotate * m_MatrixPosition * m_MatrixRevolution * m_MatrixParent;

	// 점들을 회전, 이동 시켜야하니 벡터와 월드 행렬 곱함.
	D3DXVec3TransformCoord(&vertex[0], &vertexOrigin[0], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[1], &vertexOrigin[1], &m_MatrixWorld);
}

void CKDHLine::Render(HDC hDC)
{
	MoveToEx(hDC,
		vertex[0].x,
		vertex[0].y,
		nullptr);

	LineTo(hDC,
		vertex[1].x,
		vertex[1].y);
}

void CKDHLine::Release()
{
}

void CKDHLine::SetRotateAngle(float _angle)
{
	m_revOriginAngle = _angle;
}
