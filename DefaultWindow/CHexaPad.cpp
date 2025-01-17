#include "pch.h"
#include "CHexaPad.h"
#include "CSceneMgr.h"

CHexaPad::CHexaPad()
{
	ZeroMemory(&m_ResetPosition, sizeof(D3DXVECTOR3));

	m_fScale = 20.f;
}

CHexaPad::~CHexaPad()
{
}

void CHexaPad::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_localLookAt = { 1.f, 0.f, 0.f };
	m_localScale = { 1.f, 1.f, 0.f };

	vertex[0].x = m_localPosition.x - m_fScale;
	vertex[0].y = m_localPosition.y - m_fScale;

	vertex[1].x = m_localPosition.x + m_fScale;
	vertex[1].y = m_localPosition.y - m_fScale;

	vertex[2].x = m_localPosition.x + m_fScale + m_fScale;
	vertex[2].y = m_localPosition.y + m_fScale;

	vertex[3].x = m_localPosition.x - m_fScale - m_fScale;
	vertex[3].y = m_localPosition.y + m_fScale;

	for (int i = 0; i < 4; i++)
	{
		vertexOrigin[i].x = vertex[i].x;
		vertexOrigin[i].y = vertex[i].y;
	}

	// �׵� ���.
	D3DXMatrixIdentity(&m_MatrixPosition);
	D3DXMatrixIdentity(&m_MatrixRotate);
	D3DXMatrixIdentity(&m_MatrixScale);
	D3DXMatrixIdentity(&m_MatrixRevolution);
	D3DXMatrixIdentity(&m_MatrixParent);
	D3DXMatrixIdentity(&m_MatrixWorld);

	m_fSpeed = 4.f;
}

int CHexaPad::Update()
{
	m_distance = GetDistance(m_Player->GetLocalParentPosition());
	float fPlayerDistance = GetDistance(m_Player->GetLocalPositionToWorld());

	// �÷��̾� ���� Ȯ��.
	if (fPlayerDistance <= m_fScale + m_fScale)
	{
		// ���� ���� ����.
		CSceneMgr::Get_Instance()->Set_Scene(SC_KDH);
		return 0;
	}

	if (m_distance <= 0.f)
	{
		return 0;
	}

	m_localScale.x = m_distance / 40.f;

	switch (m_iDirection)
	{
	case 0:
	{
		m_localPosition.y += m_fSpeed;
	}
	break;

	case 1:
	{
		m_localPosition.y -= m_fSpeed;
	}
	break;

	case 2:
	{
		m_localPosition.x += m_fSpeed;
	}
	break;

	case 3:
	{
		m_localPosition.x -= m_fSpeed;
	}
	break;
	}

	return 0;
}

void CHexaPad::Late_Update()
{
	// ������ �ٽ� 0,0 �������� �̵���Ŵ.
	vertexOrigin[0].x = m_ResetPosition.x - m_fScale;
	vertexOrigin[0].y = m_ResetPosition.y - m_fScale;

	vertexOrigin[1].x = m_ResetPosition.x + m_fScale;
	vertexOrigin[1].y = m_ResetPosition.y - m_fScale;

	vertexOrigin[2].x = m_ResetPosition.x + m_fScale + m_fScale;
	vertexOrigin[2].y = m_ResetPosition.y + m_fScale;

	vertexOrigin[3].x = m_ResetPosition.x - m_fScale - m_fScale;
	vertexOrigin[3].y = m_ResetPosition.y + m_fScale;

	// ũ�� ���.
	D3DXMatrixScaling(&m_MatrixScale, m_localScale.x, m_localScale.y, m_localScale.z);

	// ȸ�� ���.
	D3DXMatrixRotationZ(&m_MatrixRotate, D3DXToRadian(m_rotAngle));

	// �̵� ���.
	D3DXMatrixTranslation(&m_MatrixPosition, m_localPosition.x, m_localPosition.y, m_localPosition.z);

	// ���� ���.
	//D3DXMatrixRotationZ(&m_MatrixRevolution, D3DXToRadian(m_revolAngle));

	// �θ� ���.
	//D3DXMatrixTranslation(&m_MatrixParent, m_localParentPosition.x, m_localParentPosition.y, m_localParentPosition.z);

	// ���� ��ǥ�� ��ȯ.
	// ���� ��� = ũ�� * ����(ȸ��) * �̵� * ���� * �θ�
	m_MatrixWorld = m_MatrixScale * m_MatrixRotate * m_MatrixPosition * m_MatrixRevolution * m_MatrixParent;

	// ������ ȸ��, �̵� ���Ѿ��ϴ� ���Ϳ� ���� ��� ����.
	D3DXVec3TransformCoord(&vertex[0], &vertexOrigin[0], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[1], &vertexOrigin[1], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[2], &vertexOrigin[2], &m_MatrixWorld);
	D3DXVec3TransformCoord(&vertex[3], &vertexOrigin[3], &m_MatrixWorld);

	// ������ ����.
	D3DXVec3TransformNormal(&m_localDirection, &m_localLookAt, &m_MatrixWorld);
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

void CHexaPad::SetDirection(int _idirection)
{
	m_iDirection = _idirection;

	switch (m_iDirection)
	{
	case 0:
	{
		// ��.
		m_localPosition = { WINCX * 0.5f, m_fScale, 0.f };
		m_rotAngle = 180.f;
	}
	break;

	case 1:
	{
		// �Ʒ�.
		m_localPosition = { WINCX * 0.5f, WINCY - m_fScale, 0.f };
		m_rotAngle = 0.f;
	}
	break;

	case 2:
	{
		// ��.
		m_localPosition = { m_fScale, WINCY * 0.5f, 0.f };
		m_rotAngle = 90.f;
	}
	break;

	case 3:
	{
		// ��.
		m_localPosition = { WINCX - m_fScale, WINCY * 0.5f, 0.f };
		m_rotAngle = 270.f;
	}
	break;
	}
}
