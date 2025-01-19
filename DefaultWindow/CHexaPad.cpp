#include "pch.h"
#include "CHexaPad.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CHexaPadManager.h"
#include "CKDHScene.h"

CHexaPad::CHexaPad()
{
	ZeroMemory(&m_ResetPosition, sizeof(D3DXVECTOR3));

	m_fScale = 10.f;
	m_Player = static_cast<CKDHPlayer*>(CObjMgr::Get_Instance()->Get_Player());
}

CHexaPad::~CHexaPad()
{
}

void CHexaPad::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_localLookAt = { 1.f, 0.f, 0.f };
	m_localScale = { 1.f, 30.f, 0.f };
	m_localPosition = { 360.f, 0.f, 0.f };

	vertex[0].x = m_localPosition.x - m_fScale;
	vertex[0].y = m_localPosition.y - m_fScale;

	vertex[1].x = m_localPosition.x + m_fScale;
	vertex[1].y = m_localPosition.y - m_fScale - m_fScale;

	vertex[2].x = m_localPosition.x + m_fScale;
	vertex[2].y = m_localPosition.y + m_fScale + m_fScale;

	vertex[3].x = m_localPosition.x - m_fScale;
	vertex[3].y = m_localPosition.y + m_fScale;

	for (int i = 0; i < 4; i++)
	{
		vertexOrigin[i].x = vertex[i].x;
		vertexOrigin[i].y = vertex[i].y;
	}

	// 항등 행렬.
	D3DXMatrixIdentity(&m_MatrixPosition);
	D3DXMatrixIdentity(&m_MatrixRotate);
	D3DXMatrixIdentity(&m_MatrixScale);
	D3DXMatrixIdentity(&m_MatrixRevolution);
	D3DXMatrixIdentity(&m_MatrixParent);
	D3DXMatrixIdentity(&m_MatrixWorld);

	m_fSpeed = 4.f;
	m_rovAngle = 0.f;
	m_rotAngle = 0.f;
}

int CHexaPad::Update()
{
	// 플레이어 부모와 거리 차이.
	float fDistance = GetDistance(m_Player->GetLocalParentPosition());

	// 플레이어와 거리 차이.
	float fPlayerDistance = GetDistance(m_Player->GetLocalPositionToWorld());

	// 플레이어 접촉 확인.
	if (fPlayerDistance <= m_fScale + m_fScale)
	{
		// 게임 오버 판정.
		CSceneMgr::Get_Instance()->Set_Scene(SC_HERO);
		return OBJ_DEAD;
	}

	if (fDistance <= 2.f)
	{
		return OBJ_DEAD;
	}

	m_localScale.y = fDistance / 40.f;

	m_localPosition.x -= m_fSpeed;
	//m_localPosition -= m_localDirection * m_fSpeed;

	return 0;
}

void CHexaPad::Late_Update()
{
	if (g_bRotateAngle == true)
	{
		m_rovAngle += ROTATE_SPEED;
	}
	else
	{
		m_rovAngle -= ROTATE_SPEED;
	}

	// 점들을 다시 0,0 원점으로 이동시킴.
	vertexOrigin[0].x = m_ResetPosition.x - m_fScale;
	vertexOrigin[0].y = m_ResetPosition.y - m_fScale;

	vertexOrigin[1].x = m_ResetPosition.x + m_fScale;
	vertexOrigin[1].y = m_ResetPosition.y - m_fScale - m_fScale;

	vertexOrigin[2].x = m_ResetPosition.x + m_fScale;
	vertexOrigin[2].y = m_ResetPosition.y + m_fScale + m_fScale;

	vertexOrigin[3].x = m_ResetPosition.x - m_fScale;
	vertexOrigin[3].y = m_ResetPosition.y + m_fScale;

	// 크기 행렬.
	D3DXMatrixScaling(&m_MatrixScale, m_localScale.x, m_localScale.y, m_localScale.z);

	// 회전 행렬.
	D3DXMatrixRotationZ(&m_MatrixRotate, D3DXToRadian(m_rotAngle));

	// 이동 행렬.
	D3DXMatrixTranslation(&m_MatrixPosition, m_localPosition.x, m_localPosition.y, m_localPosition.z);

	// 공전 행렬.
	D3DXMatrixRotationZ(&m_MatrixRevolution, D3DXToRadian(m_rovAngle));

	// 부모 행렬.
	D3DXMatrixTranslation(&m_MatrixParent, m_Player->GetLocalParentPosition().x, m_Player->GetLocalParentPosition().y, m_Player->GetLocalParentPosition().z);

	// 월드 좌표로 변환.
	// 월드 행렬 = 크기 * 자전(회전) * 이동 * 공전 * 부모
	m_MatrixWorld = m_MatrixScale * m_MatrixRotate * m_MatrixPosition * m_MatrixRevolution * m_MatrixParent;

	// 점들을 회전, 이동 시켜야하니 벡터와 월드 행렬 곱함.
	D3DXVec3TransformCoord(&vertex[0], &vertexOrigin[0], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[1], &vertexOrigin[1], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[2], &vertexOrigin[2], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[3], &vertexOrigin[3], &m_MatrixWorld);

	// 방향을 구함.
	D3DXVec3TransformNormal(&m_localDirection, &m_localLookAt, &m_MatrixWorld);

	// 플레이어와 거리 차이.
	float fPlayerDistance = GetDistance(m_Player->GetLocalPositionToWorld());

	// 플레이어 접촉 확인.
	if (fPlayerDistance <= m_fScale + m_fScale)
	{
		// 게임 오버 판정.
		// 씬 재시작.
		CSceneMgr::Get_Instance()->Set_Scene(SC_HERO);
		CSceneMgr::Get_Instance()->Set_Scene(SC_KDH);
		return;
	}
}

void CHexaPad::Render(HDC hDC)
{
	MoveToEx(hDC,
		vertex[0].x,
		vertex[0].y,
		nullptr);

	LineTo(hDC,
		vertex[1].x,
		vertex[1].y);

	LineTo(hDC,
		vertex[2].x,
		vertex[2].y);

	LineTo(hDC,
		vertex[3].x,
		vertex[3].y);

	LineTo(hDC,
		vertex[0].x,
		vertex[0].y);
}

void CHexaPad::Release()
{
	
}

void CHexaPad::SetPlayer(CKDHPlayer* _player)
{
	m_Player = _player;
}

void CHexaPad::SetDirection(kDIRECTION _kDIR)
{
	m_Direction = _kDIR;

	switch (m_Direction)
	{
	case DIR_UP:
	{
		// 위.
		m_rovAngle = 270.f;
	}
	break;

	case DIR_DOWN:
	{
		// 아래.
		m_rovAngle = 90.f;
	}
	break;

	case DIR_LEFT:
	{
		// 좌.
		m_rovAngle = 180.f;
	}
	break;

	case DIR_RIGHT:
	{
		// 우.
		m_rovAngle = 0.f;
	}
	break;
	}
}
