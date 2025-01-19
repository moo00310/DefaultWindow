#include "pch.h"
#include "CStick.h"
#include "CKeyMgr.h"
#include "CSpawner.h"
#include "CSquare.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CSoundMgr.h"

CStick::CStick()
	:m_bFly(false), m_iScore(0), m_fDistance(0), m_ullLastFlyTime(0)
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
	//Check_ScreenOut();
	Check_ResetPosition();
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
		tPointArr[i].x = (LONG)m_arrWorldPoint[i].x;
		tPointArr[i].y = (LONG)m_arrWorldPoint[i].y;
	}
	Polygon(hDC, tPointArr, 4); 

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);

	//디버깅
	TCHAR cBuffer[64]; //저장할 문자열 버퍼

	_stprintf_s(cBuffer, _T("Distance: %.2f"), m_fDistance);
	TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.35f), cBuffer, (int)_tcslen(cBuffer));

	_stprintf_s(cBuffer, _T("Score: %d"), m_iScore);
	TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.15f), cBuffer, (int)_tcslen(cBuffer));

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
		if (m_bFly)
		{
			return;
		}

		m_tInfo.vPos -= 0.1f * (m_tInfo.vPos - m_vWorldBackPosition);
		//m_tInfo.vPos = m_vWorldBackPosition;
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		if (m_bFly)
		{
			return;
		}

		Check_Hit();
		m_bFly = true;
		m_ullLastFlyTime = GetTickCount64();
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

void CStick::Check_Hit()
{
	list<CObj*> LeftList = CObjMgr::Get_Instance()->Get_List()[OBJ_MONSTER];
	list<CObj*> RightList = CObjMgr::Get_Instance()->Get_List()[OBJ_BULLET];
		
	if (!LeftList.size() || !RightList.size())
	{
		CSoundMgr::Get_Instance()->PlayEvent("event:/Built_Fail");
		return;
	}

	CObj* pLeft = *LeftList.begin();
	CObj* pRight = *RightList.begin();

	if (!pLeft || !pRight)
	{
		CSoundMgr::Get_Instance()->PlayEvent("event:/Built_Fail");
		m_fDistance = WINCX;
		return;
	}

	D3DXVECTOR3 vLeft{};
	D3DXVECTOR3 vRight{};
	if (CSquare* pLeftSquare = dynamic_cast<CSquare*>(pLeft))
	{
		vLeft = pLeftSquare->Get_World_Center();
	}
	if (CSquare* pRightSquare = dynamic_cast<CSquare*>(pRight))
	{
		vRight = pRightSquare->Get_World_Center();
	}

	m_fDistance = abs(vLeft.x - vRight.x);

	if (m_fDistance < JUDGE_WINDOW)
	{
		++m_iScore;
		Assemble_Parts();
		CSoundMgr::Get_Instance()->PlayEvent("event:/Built_Success");
	}
	else
	{
		CSoundMgr::Get_Instance()->PlayEvent("event:/Built_Fail");
	}
}

void CStick::Assemble_Parts()
{
	list<CObj*> LeftList = CObjMgr::Get_Instance()->Get_List()[OBJ_MONSTER];
	list<CObj*> RightList = CObjMgr::Get_Instance()->Get_List()[OBJ_BULLET];

	if (!LeftList.size() || !RightList.size())
	{
		return;
	}

	CObj* pLeft = *LeftList.begin();
	CObj* pRight = *RightList.begin();

	pLeft->Set_Dead();
	pRight->Set_Dead();

	CObj* pObj = CAbstractFactory<CSquare>::Create(WINCX * 0.5f, WINCY * 0.4f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, pObj);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(pObj))
	{
		pSquare->Set_Assembled();
	}

	//pLeft->Set_Pos(WINCX * 0.5f, WINCY * 0.1f);
	//pRight->Set_Pos(WINCX * 0.5f, WINCY * 0.1f);
}

void CStick::Check_ResetPosition()
{
	if (m_bFly)
	{
		if (m_ullLastFlyTime + FLY_INTERVAL < GetTickCount64())
		{
			m_tInfo.vPos = m_vOriginPosition;
			m_bFly = false;
		}
	}
}
