#include "pch.h"
#include "CSquare.h"
#include "CObjMgr.h"
#include "CSpawner.h"
#include "CSoundMgr.h"

CSquare::CSquare()
	:m_fAngle(0.f), m_iRotPoint(0), m_bRollLeft(false), m_ullWaitTime(0), m_bFall(false),
	m_pBankPoint(nullptr), m_pNotePoint(nullptr), m_iNote(0), m_fCurSpeed(0.f), m_fTime(0.f)
{
	ZeroMemory(&m_arrLocalPoint, sizeof(m_arrLocalPoint));
	ZeroMemory(&m_arrWorldPoint, sizeof(m_arrWorldPoint));

	ZeroMemory(&m_vLocalPoint_Center, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vWorldPoint_Center, sizeof(D3DXVECTOR3));
}

CSquare::~CSquare()
{
	Release();
}

void CSquare::Set_RollLeft(bool _b)
{
	m_bRollLeft = _b;

	if (m_bRollLeft)
	{
		m_iRotPoint = 3;
	}
	else
	{
		m_iRotPoint = 2;
	}
}

void CSquare::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	//m_fSize = SIDE;
	//m_fSpeed = 4.f;

	m_arrLocalPoint[0] = { -SIDE * 0.5f, -SIDE * 0.5f, 0.f };
	m_arrLocalPoint[1] = { SIDE * 0.5f, -SIDE * 0.5f, 0.f };
	m_arrLocalPoint[2] = { SIDE * 0.5f, SIDE * 0.5f, 0.f };
	m_arrLocalPoint[3] = { -SIDE * 0.5f, SIDE * 0.5f, 0.f };

	m_vLocalPoint_Center = { 0.f, 0.f, 0.f };

	Update_WorldMatrix();

	//if (m_bLeft)
	//{
	//	m_iRotPoint = 3;
	//}
	//else
	//{
	//	m_iRotPoint = 2;
	//}
	

	m_ullWaitTime = GetTickCount64();

	//m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
	//m_pBankPoint =  CSoundMgr::Get_Instance()->LoadBank("bank:/Note");

	//m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
	//m_pNotePoint->setParameterByName("Note", (float)(rand() % 6));
}

int CSquare::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!Wait_Time())
	{
		if (!m_bFall)
		{
			Change_Speed();
			Roll_Corners();
		}
		else
		{
			Fall();
		}
	}
	Update_WorldMatrix();

	return OBJ_NOEVENT;
}

void CSquare::Update_WorldMatrix()
{
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMATRIX matTransMove;
	D3DXMatrixIdentity(&matTransMove);
	D3DXMatrixTranslation(&matTransMove, -m_arrLocalPoint[m_iRotPoint].x, -m_arrLocalPoint[m_iRotPoint].y, -m_arrLocalPoint[m_iRotPoint].z);

	D3DXMATRIX matRotZ;
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);

	D3DXMATRIX matTransBack;
	D3DXMatrixIdentity(&matTransBack);
	D3DXMatrixTranslation(&matTransBack, m_arrLocalPoint[m_iRotPoint].x, m_arrLocalPoint[m_iRotPoint].y, m_arrLocalPoint[m_iRotPoint].z);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	// 행렬 조합: 스케일 * (중심 이동 * 회전 * 원위치 이동) * 최종 이동
	m_tInfo.matWorld = matScale * (matTransMove * matRotZ * matTransBack) * matTrans;

	//m_tInfo.matWorld = matScale * matRotZ * matTrans;

}

void CSquare::Roll_Corners()
{
	if (m_bRollLeft)
	{
		//각도를 증가 시킨다.
		m_fAngle -= D3DXToRadian(m_fCurSpeed);

		//충돌 체크할 포인트 설정
		int iCheckPoint = m_iRotPoint + 1;
		if (iCheckPoint > 3)
		{
			iCheckPoint = 0;
		}

		//if (abs(m_vWorldPoint[iCheckPoint].y - WINCY * 0.5f) < 1e-6f)
		//{
		//	m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
		//	m_pNotePoint->setParameterByName("Note", (float)(m_iNote++));
		//}

		//충돌 체크할 포인트가 충돌하면 
		if (m_arrWorldPoint[iCheckPoint].y > WINCY * 0.5f)
		{
			if (m_iNote < 5)
			{
				m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
			}
			OnVertexTouch();
			//현재 회전의 중점으로 하는 포인트에 따라, 사각형의 중점을 이동 시킨다.[하드코딩, 규칙을 못 찾음]
			//처음 시작점(3) 포인트 차이만큼 이동시키는 것 같긴함
			switch (m_iRotPoint)
			{
			case 0:
				m_tInfo.vPos -= {2.f * SIDE, 0.f, 0.f};
				break;
			case 1:
				m_tInfo.vPos -= {1.f * SIDE, 1.f * SIDE, 0.f};
				break;
			case 2:
				m_tInfo.vPos -= {0.f, 0.f, 0.f};
				break;
			case 3:
				m_tInfo.vPos -= {1.f * SIDE, -1.0f * SIDE, 0.f};
				break;
			default:
				break;
			}

			//체크 하던 포인트로 회전 중점을 변경
			m_iRotPoint = iCheckPoint;
		}
	}
	else
	{
		//각도를 증가 시킨다.
		m_fAngle += D3DXToRadian(m_fCurSpeed);

		//충돌 체크할 포인트 설정
		int iCheckPoint = m_iRotPoint - 1;
		if (iCheckPoint < 0)
		{
			iCheckPoint = 3;
		}

		//충돌 체크할 포인트가 충돌하면
		if (m_arrWorldPoint[iCheckPoint].y > WINCY * 0.5f)
		{
			OnVertexTouch();
			//현재 회전의 중점으로 하는 포인트에 따라, 사각형의 중점을 이동 시킨다.[하드코딩, 규칙을 못 찾음]
			//처음 시작점(3) 포인트 차이만큼 이동시키는 것 같긴함
			switch (m_iRotPoint)
			{
			case 0:
				m_tInfo.vPos += {1.f * SIDE, -1.0f * SIDE, 0.f};
				break;
			case 1:
				m_tInfo.vPos += {2.f * SIDE, 0.f, 0.f};
				break;
			case 2:
				m_tInfo.vPos += {1.f * SIDE, 1.f * SIDE, 0.f};
				break;
			case 3:
				m_tInfo.vPos += {0.f, 0.f, 0.f};
				break;
			default:
				break;
			}

			//체크 하던 포인트로 회전 중점을 변경
			m_iRotPoint = iCheckPoint;
		}
	}
}

void CSquare::Roll()
{
	float fAngle = D3DXToRadian(1.f);  // 각도 증가 (1도씩)
	float fL = SIDE * 2.f;  // 한 변의 길이
	float fR = fL * sqrtf(2.f);  // 대각선 절반 길이

	m_fAngle += fAngle;  // 각도 증가

	float fY = WINCY * 0.5f - SIDE * 0.5f;

	// 중점의 위치 계산
	m_tInfo.vPos.x = SIDE * m_fAngle;  // 중점의 수평 이동
	m_tInfo.vPos.y = float(fY - SIDE * (1 + (sqrtf(2.f) - 1) * cos(PI * m_fAngle)));  // 중점의 수직 이동

}

void CSquare::Check_ScreenOut()
{
	if (m_vWorldPoint_Center.x < 0.f || m_vWorldPoint_Center.x >(float)WINCX)
	{
		Set_Dead();
	}
}

bool CSquare::Wait_Time()
{
	return m_ullWaitTime + 1000 > GetTickCount64();
}

void CSquare::Change_Speed()
{
	//땅에 닿았을때 느려졌다가...세워졌을 때 빨라져야함
	m_fTime += 0.3f;
	m_fCurSpeed = abs(sin(m_fTime)) * m_fSpeed;
}

void CSquare::Fall()
{
	m_tInfo.vPos += {0.f, FALL_SPEED, 0.f};
}

void CSquare::OnVertexTouch()
{
	m_pNotePoint->setParameterByName("Note", (float)(m_iNote++));
	if (m_iNote == ROLL_COUNT + 1)
	{
		m_bFall = true;
	}
}

void CSquare::Render(HDC hDC)
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

	//중점
	D3DXVec3TransformCoord(&m_vWorldPoint_Center, &m_vLocalPoint_Center, &m_tInfo.matWorld);
	int iEllipseSize = (int)(SIDE * 0.25f);
	Ellipse(hDC, 
		(int)(m_vWorldPoint_Center.x - iEllipseSize),
		(int)(m_vWorldPoint_Center.y - iEllipseSize),
		(int)(m_vWorldPoint_Center.x + iEllipseSize),
		(int)(m_vWorldPoint_Center.y + iEllipseSize));

	TCHAR cBuffer[64]; //저장할 문자열 버퍼
	//// 문자열로 변환하여 출력 준비
	//for (int i = 0; i < 4; ++i)
	//{
	//	_stprintf_s(cBuffer, _T("(%d)[%.0f, %.0f]"), i, m_vWorldPoint[i].x, m_vWorldPoint[i].y);
	//	TextOut(hDC, (int)m_vWorldPoint[i].x, (int)m_vWorldPoint[i].y, cBuffer, (int)_tcslen(cBuffer));
	//}

	// 문자열로 변환하여 출력 준비
	/*for (int i = 0; i < 4; ++i)
	{
		_stprintf_s(cBuffer, _T("(%d)"), i);
		TextOut(hDC, (int)m_arrWorldPoint[i].x, (int)m_arrWorldPoint[i].y, cBuffer, (int)_tcslen(cBuffer));
	}

	_stprintf_s(cBuffer, _T("(O)[%.0f, %.0f]"), m_tInfo.vPos.x, m_tInfo.vPos.y);
	TextOut(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, cBuffer, (int)_tcslen(cBuffer));

	_stprintf_s(cBuffer, _T("CurSpeed: %.2f"), m_fCurSpeed);
	TextOut(hDC, 0, 0, cBuffer, (int)_tcslen(cBuffer));*/
}

void CSquare::Release()
{
	list<CObj*> List = CObjMgr::Get_Instance()->Get_List()[OBJ_SHIELD];
	CObj* pObj = *List.begin();

	if (CSpawner* pSpawner = dynamic_cast<CSpawner*>(pObj))
	{
		if (m_bRollLeft)
		{
			pSpawner->Set_LeftSquare(nullptr);
		}
		else
		{
			pSpawner->Set_RightSquare(nullptr);
		}
	}
}

void CSquare::Late_Update()
{
	//Check_ScreenOut();
}
