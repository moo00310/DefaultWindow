#include "pch.h"
#include "CPlayer_SSH_Fire.h"

#include "CKeyMgr.h"

CPlayer_SSH_Fire::CPlayer_SSH_Fire()
{
}

CPlayer_SSH_Fire::~CPlayer_SSH_Fire()
{
}

void CPlayer_SSH_Fire::Initialize()
{
    m_tInfo.vPos = { 0.f, 300.f, 0.f };
    D3DXMatrixIdentity(&m_tInfo.matWorld);

    m_vPoint = { 0.f, 0.f, 0.f };
    m_vOriginPoint = m_vPoint;

    m_eRender = RENDER_GAMEOBJECT;
    m_bRev = true; // �� �� �ϳ��� �ϴ� ���ƾ��ϱ⶧���� Ʈ��
}

int CPlayer_SSH_Fire::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    D3DXMATRIX matScale, matRotZ, matTranse, matRevZ, matParrent;

    // ũ�� ��ȯ ����� ����� �Լ�
    // D3DXMatrixScaling(������� ������ ����� �ּ�, X����, Y����, Z����)

    // ȸ�� ��ȯ ����� ����� �Լ�
    // D3DXMatrixRotationZ(������� ������ ����� �ּ�, ȸ�� ����(����))
    // 
    // ��ġ ��ȯ ����� ����� �Լ�
    // D3DXMatrixTranslation(������� ������ ����� �ּ�, x��ġ, y��ġ, z��ġ)

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
    D3DXMatrixTranslation(&matTranse, -50.f, 0.f, 0.f);
    D3DXMatrixRotationZ(&matRevZ, D3DXToRadian(m_fAngle));

    if (m_fAngle > m_fMaxAngle)
        m_fAngle -= m_fAngle;

    //�����̶�� ����
    if (m_bRev)
    {
        m_fAngle += m_fRevSpeed;
    }

    //�ٲ��� �ʾҴٸ� ���ڸ�
    if (!m_bRev)
    {
        D3DXMatrixTranslation(&matParrent, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
    }
    // �ٲ��ٸ� Ÿ���߽����� ����
    else if (m_bRev)
    {
        if (CPlayer_SSH* Temp = dynamic_cast<CPlayer_SSH*>(m_pTarget))
        {
            D3DXMatrixTranslation(&matParrent, Temp->Get_vPoint().x, Temp->Get_vPoint().y, 0.f);
            // �����ϴ� ��ġ�� ���� ��ġ�� �Ѱ��༭ Ÿ���� �� ��ġ �߽����� ������ �� �ֵ��� ��
            m_tInfo.vPos = Temp->Get_vPoint();
        }
    }

    m_tInfo.matWorld = matScale * matRotZ * matTranse * matRevZ * matParrent;

    m_vPoint = m_vOriginPoint;
    D3DXVec3TransformCoord(&m_vPoint, &m_vPoint, &m_tInfo.matWorld);

    Key_Input();
    return OBJ_NOEVENT;
}

void CPlayer_SSH_Fire::Late_Update()
{
}

void CPlayer_SSH_Fire::Render(HDC hDC)
{
    Ellipse(hDC,
        int(m_vPoint.x - 20.f),
        int(m_vPoint.y - 20.f),
        int(m_vPoint.x + 20.f),
        int(m_vPoint.y + 20.f));

    TCHAR szStatus[100]{};

    swprintf_s(szStatus, L"�� ���� : %.2f", m_fAngle);
    TextOut(hDC, 500, 20, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"���� ��ġ X : %.2f, Y : %.2f", m_vPoint.x, m_vPoint.y);
    TextOut(hDC, 500, 40, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"��");
    TextOut(hDC, (int)m_vPoint.x, (int)m_vPoint.y, szStatus, lstrlen(szStatus));
}

void CPlayer_SSH_Fire::Release()
{
}

void CPlayer_SSH_Fire::Key_Input()
{
    if (m_bRev)
    {
        if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
        {
            m_fAngle -= 5.f;
        }
        else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
        {
            m_fAngle += 5.f;
        }
    }
}
