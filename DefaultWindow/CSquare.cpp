#include "pch.h"
#include "CSquare.h"
#include "CObjMgr.h"
#include "CSpawner.h"
#include "CSoundMgr.h"

CSquare::CSquare()
	:m_fAngle(0.f), m_fSize(0.f), m_iRotPoint(0), m_bLeft(false), m_ullWaitTime(0),
	m_pBankPoint(nullptr), m_pNotePoint(nullptr), m_iNote(0)
{
	ZeroMemory(&m_vLocalPoint, sizeof(m_vLocalPoint));
	ZeroMemory(&m_vWorldPoint, sizeof(m_vWorldPoint));

	ZeroMemory(&m_vLocalPoint_Center, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vWorldPoint_Center, sizeof(D3DXVECTOR3));
}

CSquare::~CSquare()
{
	Release();
}

void CSquare::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;

	m_fSize = SIDE;
	//m_fSpeed = 4.f;

	m_vLocalPoint[0] = { -m_fSize * 0.5f, -m_fSize * 0.5f, 0.f };
	m_vLocalPoint[1] = { m_fSize * 0.5f, -m_fSize * 0.5f, 0.f };
	m_vLocalPoint[2] = { m_fSize * 0.5f, m_fSize * 0.5f, 0.f };
	m_vLocalPoint[3] = { -m_fSize * 0.5f, m_fSize * 0.5f, 0.f };

	m_vLocalPoint_Center = { 0.f, 0.f, 0.f };

	Update_WorldMatrix();

	m_iRotPoint = 3;

	m_ullWaitTime = GetTickCount64();

	//m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
	//m_pBankPoint =  CSoundMgr::Get_Instance()->LoadBank("bank:/Note");

	m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
	m_pNotePoint->setParameterByName("Note", (float)(rand() % 6));
}

int CSquare::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!Wait_Time())
	{
		Roll_Corners();
		//Roll();
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
	D3DXMatrixTranslation(&matTransMove, -m_vLocalPoint[m_iRotPoint].x, -m_vLocalPoint[m_iRotPoint].y, -m_vLocalPoint[m_iRotPoint].z);

	D3DXMATRIX matRotZ;
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);

	D3DXMATRIX matTransBack;
	D3DXMatrixIdentity(&matTransBack);
	D3DXMatrixTranslation(&matTransBack, m_vLocalPoint[m_iRotPoint].x, m_vLocalPoint[m_iRotPoint].y, m_vLocalPoint[m_iRotPoint].z);

	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	// ��� ����: ������ * (�߽� �̵� * ȸ�� * ����ġ �̵�) * ���� �̵�
	m_tInfo.matWorld = matScale * (matTransMove * matRotZ * matTransBack) * matTrans;

	//m_tInfo.matWorld = matScale * matRotZ * matTrans;

}

void CSquare::Roll_Corners()
{
	if (m_bLeft)
	{
		//������ ���� ��Ų��.
		m_fAngle -= D3DXToRadian(m_fSpeed);

		//�浹 üũ�� ����Ʈ ����
		int iCheckPoint = m_iRotPoint + 1;
		if (iCheckPoint > 3)
		{
			iCheckPoint = 0;
		}

		//�浹 üũ�� ����Ʈ�� �浹�ϸ�
		if (m_vWorldPoint[iCheckPoint].y > WINCY * 0.5f)
		{
			m_pNotePoint = CSoundMgr::Get_Instance()->PlayEvent("event:/Note");
			//m_pNotePoint->setParameterByName("Note", (float)(m_iNote++));
			//CSoundMgr::Get_Instance()->Update();
			//m_pNotePoint->start();

			//���� ȸ���� �������� �ϴ� ����Ʈ�� ����, �簢���� ������ �̵� ��Ų��.[�ϵ��ڵ�, ��Ģ�� �� ã��]
			//ó�� ������(3) ����Ʈ ���̸�ŭ �̵���Ű�� �� ������
			switch (m_iRotPoint)
			{
			case 0:
				m_tInfo.vPos -= {2.f * m_fSize, 0.f, 0.f};
				break;
			case 1:
				m_tInfo.vPos -= {1.f * m_fSize, 1.f * m_fSize, 0.f};
				break;
			case 2:
				m_tInfo.vPos -= {0.f, 0.f, 0.f};
				break;
			case 3:
				m_tInfo.vPos -= {1.f * m_fSize, -1.0f * m_fSize, 0.f};
				break;
			default:
				break;
			}

			//üũ �ϴ� ����Ʈ�� ȸ�� ������ ����
			m_iRotPoint = iCheckPoint;
		}
	}
	else
	{
		//������ ���� ��Ų��.
		m_fAngle += D3DXToRadian(m_fSpeed);

		//�浹 üũ�� ����Ʈ ����
		int iCheckPoint = m_iRotPoint - 1;
		if (iCheckPoint < 0)
		{
			iCheckPoint = 3;
		}

		//�浹 üũ�� ����Ʈ�� �浹�ϸ�
		if (m_vWorldPoint[iCheckPoint].y > WINCY * 0.5f)
		{
			//���� ȸ���� �������� �ϴ� ����Ʈ�� ����, �簢���� ������ �̵� ��Ų��.[�ϵ��ڵ�, ��Ģ�� �� ã��]
			//ó�� ������(3) ����Ʈ ���̸�ŭ �̵���Ű�� �� ������
			switch (m_iRotPoint)
			{
			case 0:
				m_tInfo.vPos += {1.f * m_fSize, -1.0f * m_fSize, 0.f};
				break;
			case 1:
				m_tInfo.vPos += {2.f * m_fSize, 0.f, 0.f};
				break;
			case 2:
				m_tInfo.vPos += {1.f * m_fSize, 1.f * m_fSize, 0.f};
				break;
			case 3:
				m_tInfo.vPos += {0.f, 0.f, 0.f};
				break;
			default:
				break;
			}

			//üũ �ϴ� ����Ʈ�� ȸ�� ������ ����
			m_iRotPoint = iCheckPoint;
		}
	}
}

void CSquare::Roll()
{
	float fAngle = D3DXToRadian(1.f);  // ���� ���� (1����)
	float fL = m_fSize * 2.f;  // �� ���� ����
	float fR = fL * sqrtf(2.f);  // �밢�� ���� ����

	m_fAngle += fAngle;  // ���� ����

	float fY = WINCY * 0.5f - m_fSize * 0.5f;

	// ������ ��ġ ���
	m_tInfo.vPos.x = m_fSize * m_fAngle;  // ������ ���� �̵�
	m_tInfo.vPos.y = float(fY - m_fSize * (1 + (sqrtf(2.f) - 1) * cos(PI * m_fAngle)));  // ������ ���� �̵�

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

void CSquare::Render(HDC hDC)
{
	//�簢��
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vLocalPoint[i], &m_tInfo.matWorld);
	}

	MoveToEx(hDC, (int)m_vWorldPoint[0].x, (int)m_vWorldPoint[0].y, nullptr);
	LineTo(hDC, (int)m_vWorldPoint[1].x, (int)m_vWorldPoint[1].y);
	LineTo(hDC, (int)m_vWorldPoint[2].x, (int)m_vWorldPoint[2].y);
	LineTo(hDC, (int)m_vWorldPoint[3].x, (int)m_vWorldPoint[3].y);
	LineTo(hDC, (int)m_vWorldPoint[0].x, (int)m_vWorldPoint[0].y);
	
	//����
	D3DXVec3TransformCoord(&m_vWorldPoint_Center, &m_vLocalPoint_Center, &m_tInfo.matWorld);
	int iEllipseSize = (int)(m_fSize * 0.25f);
	Ellipse(hDC, 
		(int)(m_vWorldPoint_Center.x - iEllipseSize),
		(int)(m_vWorldPoint_Center.y - iEllipseSize),
		(int)(m_vWorldPoint_Center.x + iEllipseSize),
		(int)(m_vWorldPoint_Center.y + iEllipseSize));

	TCHAR cBuffer[64]; //������ ���ڿ� ����
	//// ���ڿ��� ��ȯ�Ͽ� ��� �غ�
	//for (int i = 0; i < 4; ++i)
	//{
	//	_stprintf_s(cBuffer, _T("(%d)[%.0f, %.0f]"), i, m_vWorldPoint[i].x, m_vWorldPoint[i].y);
	//	TextOut(hDC, (int)m_vWorldPoint[i].x, (int)m_vWorldPoint[i].y, cBuffer, (int)_tcslen(cBuffer));
	//}

	// ���ڿ��� ��ȯ�Ͽ� ��� �غ�
	for (int i = 0; i < 4; ++i)
	{
		_stprintf_s(cBuffer, _T("(%d)"), i);
		TextOut(hDC, (int)m_vWorldPoint[i].x, (int)m_vWorldPoint[i].y, cBuffer, (int)_tcslen(cBuffer));
	}

	_stprintf_s(cBuffer, _T("(O)[%.0f, %.0f]"), m_tInfo.vPos.x, m_tInfo.vPos.y);
	TextOut(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, cBuffer, (int)_tcslen(cBuffer));
}

void CSquare::Release()
{
	list<CObj*> List = CObjMgr::Get_Instance()->Get_List()[OBJ_SHIELD];
	CObj* pObj = *List.begin();

	if (CSpawner* pSpawner = dynamic_cast<CSpawner*>(pObj))
	{
		if (m_bLeft)
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
	Check_ScreenOut();
}
