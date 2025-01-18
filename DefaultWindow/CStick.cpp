#include "pch.h"
#include "CStick.h"
#include "CKeyMgr.h"

CStick::CStick()
	:m_bFly(false)
{
	ZeroMemory(&m_arrLocalPoint, sizeof(m_arrLocalPoint));
	ZeroMemory(&m_arrWorldPoint, sizeof(m_arrWorldPoint));
	ZeroMemory(&m_vWorldBackPosition, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vLocalBackPosition, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vOriginPosition, sizeof(D3DXVECTOR3));
}

CStick::~CStick()
{
    Release();
}

void CStick::Initialize()
{
    m_eRender = RENDER_GAMEOBJECT;

    m_arrLocalPoint[0] = { -STICK_WIDTH * 0.5f, -STICK_HEIGHT* 0.5f, 0.f };
    m_arrLocalPoint[1] = { STICK_WIDTH * 0.5f, -STICK_HEIGHT * 0.5f, 0.f };
    m_arrLocalPoint[2] = { STICK_WIDTH * 0.5f, STICK_HEIGHT * 0.5f, 0.f };
    m_arrLocalPoint[3] = { -STICK_WIDTH * 0.5f, STICK_HEIGHT * 0.5f, 0.f };

	m_vLocalBackPosition = { 0.f, PULL_LENGTH, 0.f };

	Update_WorldMatrix();

	//최초 위치
	D3DXVECTOR3 tZeroPoint{ 0.f, 0.f, 0.f };
	D3DXVec3TransformCoord(&m_vOriginPosition, &tZeroPoint, &m_tInfo.matWorld);
	//후퇴 위치
	D3DXVec3TransformCoord(&m_vWorldBackPosition, &m_vLocalBackPosition, &m_tInfo.matWorld);
}

int CStick::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

	Input_Key();
	Check_ScreenOut();
	if (m_bFly)
	{
		Fly();
	}

	Update_WorldMatrix();
    return OBJ_NOEVENT;
}

void CStick::Late_Update()
{
}

void CStick::Render(HDC hDC)
{
	//사각형
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_arrWorldPoint[i], &m_arrLocalPoint[i], &m_tInfo.matWorld);
	}

	MoveToEx(hDC, (int)m_arrWorldPoint[0].x, (int)m_arrWorldPoint[0].y, nullptr);
	LineTo(hDC, (int)m_arrWorldPoint[1].x, (int)m_arrWorldPoint[1].y);
	LineTo(hDC, (int)m_arrWorldPoint[2].x, (int)m_arrWorldPoint[2].y);
	LineTo(hDC, (int)m_arrWorldPoint[3].x, (int)m_arrWorldPoint[3].y);
	LineTo(hDC, (int)m_arrWorldPoint[0].x, (int)m_arrWorldPoint[0].y);

	//사각형 색칠
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	POINT tPointArr[4] = {};
	for (int i = 0; i < 4; ++i)
	{
		tPointArr[i].x = m_arrWorldPoint[i].x;
		tPointArr[i].y = m_arrWorldPoint[i].y;
	}
	Polygon(hDC, tPointArr, 4);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

}

void CStick::Release()
{
}

void CStick::Update_WorldMatrix()
{
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMATRIX matRotZ;
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	//후퇴 위치
	//D3DXVec3TransformCoord(&m_vWorldBackPosition, &m_vLocalBackPosition, &m_tInfo.matWorld);
}

void CStick::Input_Key()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		m_tInfo.vPos = m_vWorldBackPosition;
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bFly = true;
	}
}

void CStick::Set_OriginPosition()
{
	//m_vOriginPosition
}

void CStick::Set_BackPosition()
{
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMATRIX matRotZ;
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

}

void CStick::Fly()
{
	m_tInfo.vPos += {0.f, -FLY_SPEED, 0.f};
}

void CStick::Check_ScreenOut()
{
	if (m_tInfo.vPos.y < -(STICK_HEIGHT))
	{
		m_tInfo.vPos = m_vOriginPosition;
		m_bFly = false;
	}
}
