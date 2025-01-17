#include "pch.h"
#include "CKDHPlayer.h"

CKDHPlayer::CKDHPlayer()
{
	ZeroMemory(&m_ResetPosition, sizeof(D3DXVECTOR3));
}

CKDHPlayer::~CKDHPlayer()
{
	Release();
}

void CKDHPlayer::Initialize()
{
	m_fParentScale = 30.f;
	m_fScale = 10.f;

	// 부모 위치.
	m_localParentPosition = { WINCX * 0.5f, WINCY * 0.5f, 0.f };

	// 부모 기준 나의 위치.
	m_localPosition = { 50.f, 0.f, 0.f };

	m_localLookAt = { 0.f, -1.f, 0.f };
	m_localScale = { 1.f, 1.f, 0.f };

	vertex[0].x = m_localPosition.x;
	vertex[0].y = m_localPosition.y - m_fScale;

	vertex[1].x = m_localPosition.x - m_fScale;
	vertex[1].y = m_localPosition.y + m_fScale;

	vertex[2].x = m_localPosition.x + m_fScale;
	vertex[2].y = m_localPosition.y + m_fScale;

	/*vertex[3].x = m_localPosition.x - m_scale;
	vertex[3].y = m_localPosition.y + m_scale;*/

	for (int i = 0; i < 3; i++)
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

	m_fSpeed = 5.f;
	m_revolAngle = 0.f;
	m_rotAngle = 90.f;
	m_moreScale = 0.1f;
	m_revolSpeed = 5.f;
	m_rotSpeed = 1.f;
}

int CKDHPlayer::Update()
{
	Key_Input();

	return 0;
}

void CKDHPlayer::Late_Update()
{
	// 점들을 다시 0,0 원점으로 이동시킴.
	vertexOrigin[0].x = m_ResetPosition.x;
	vertexOrigin[0].y = m_ResetPosition.y - m_fScale;

	vertexOrigin[1].x = m_ResetPosition.x - m_fScale;
	vertexOrigin[1].y = m_ResetPosition.y + m_fScale;

	vertexOrigin[2].x = m_ResetPosition.x + m_fScale;
	vertexOrigin[2].y = m_ResetPosition.y + m_fScale;

	/*vertexOrigin[3].x = m_ResetPosition.x - m_scale;
	vertexOrigin[3].y = m_ResetPosition.y + m_scale;*/

	// 크기 행렬.
	D3DXMatrixScaling(&m_MatrixScale, m_localScale.x, m_localScale.y, m_localScale.z);

	// 회전 행렬.
	D3DXMatrixRotationZ(&m_MatrixRotate, D3DXToRadian(m_rotAngle));

	// 이동 행렬.
	D3DXMatrixTranslation(&m_MatrixPosition, m_localPosition.x, m_localPosition.y, m_localPosition.z);

	// 공전 행렬.
	D3DXMatrixRotationZ(&m_MatrixRevolution, D3DXToRadian(m_revolAngle));

	// 부모 행렬.
	D3DXMatrixTranslation(&m_MatrixParent, m_localParentPosition.x, m_localParentPosition.y, m_localParentPosition.z);

	// 월드 좌표로 변환.
	// 월드 행렬 = 크기 * 자전(회전) * 이동 * 공전 * 부모
	m_MatrixWorld = m_MatrixScale * m_MatrixRotate * m_MatrixPosition * m_MatrixRevolution * m_MatrixParent;

	// 점들을 회전, 이동 시켜야하니 벡터와 월드 행렬 곱함.
	D3DXVec3TransformCoord(&vertex[0], &vertexOrigin[0], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[1], &vertexOrigin[1], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[2], &vertexOrigin[2], &m_MatrixWorld);
	//D3DXVec3TransformCoord(&vertex[3], &vertexOrigin[3], &m_MatrixWorld);

	// 방향을 구함.
	D3DXVec3TransformNormal(&m_localDirection, &m_localLookAt, &m_MatrixWorld);
}

void CKDHPlayer::Render(HDC hDC)
{
	Ellipse(hDC,
		m_localParentPosition.x - m_fParentScale,
		m_localParentPosition.y - m_fParentScale,
		m_localParentPosition.x + m_fParentScale,
		m_localParentPosition.y + m_fParentScale);

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

	/*LineTo(g_DubbleBufferHDC,
		vertex[3].x,
		vertex[3].y);*/

	LineTo(hDC,
		vertex[0].x,
		vertex[0].y);
}

void CKDHPlayer::Release()
{
}

void CKDHPlayer::Key_Input()
{
	/*if (GetAsyncKeyState(VK_UP))
	{
		m_localParentPosition.y -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_localParentPosition.y += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_localParentPosition.x -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_localParentPosition.x += m_fSpeed;
	}*/

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_revolAngle -= m_revolSpeed;
		//m_rotAngle -= m_rotSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_revolAngle += m_revolSpeed;
		//m_rotAngle -= m_rotSpeed;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		//m_localPosition += m_localDirection * m_fMoveSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		//m_localPosition -= m_localDirection * m_fMoveSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_localScale.x += m_moreScale;
	}
}
