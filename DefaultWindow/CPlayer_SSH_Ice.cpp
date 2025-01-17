#include "pch.h"
#include "CPlayer_SSH_Ice.h"

#include "CKeyMgr.h"

CPlayer_SSH_Ice::CPlayer_SSH_Ice()
{
}

CPlayer_SSH_Ice::~CPlayer_SSH_Ice()
{
}

void CPlayer_SSH_Ice::Initialize()
{
    m_tInfo.vPos = { 400.f, 300.f, 0.f };
    D3DXMatrixIdentity(&m_tInfo.matWorld);

    m_vPoint = { 0.f, 0.f, 0.f };
    m_vOriginPoint = m_vPoint;

    m_eRender = RENDER_GAMEOBJECT;
}

int CPlayer_SSH_Ice::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    // 바꼈다면 회전
    //if (m_bChange)
    //{
    //    m_fAngle += 3.f;
    //}

    D3DXMATRIX matScale, matRotZ, matTranse, matRevZ, matParrent;

    // 크기 변환 행렬을 만드는 함수
    // D3DXMatrixScaling(결과값을 저장할 행렬의 주소, X배율, Y배율, Z배율)

    // 회전 변환 행렬을 만드는 함수
    // D3DXMatrixRotationZ(결과값을 저장할 행렬의 주소, 회전 각도(라디안))
    // 
    // 위치 변환 행렬을 만드는 함수
    // D3DXMatrixTranslation(결과값을 저장할 행렬의 주소, x위치, y위치, z위치)

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
    D3DXMatrixTranslation(&matTranse, -100.f, 0.f, 0.f);
    D3DXMatrixRotationZ(&matRevZ, D3DXToRadian(m_fAngle));

    // 바뀌지 않았다면 제자리에서 대기
    if (!m_bChange)
    {
        D3DXMatrixTranslation(&matParrent, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
    }
    // 바뀌었다면 타깃 중심으로 공전
    else if(m_bChange)
    {
        // 타깃(불) 중심으로 공전, 
        if (CPlayer_SSH* Temp = dynamic_cast<CPlayer_SSH*>(m_pTarget))
        {
            D3DXMatrixTranslation(&matParrent, Temp->Get_vPoint().x, Temp->Get_vPoint().y, 0.f);
            // 공전하던 타깃의 중심를 본인의 중심으로 넘겨줌
            m_tInfo.vPos = Temp->Get_vPoint();
        }
    }

    m_tInfo.matWorld = matScale * matRotZ * matTranse * matRevZ * matParrent;

    m_vPoint = m_vOriginPoint;
    D3DXVec3TransformCoord(&m_vPoint, &m_vPoint, &m_tInfo.matWorld);

    Key_Input();
    return OBJ_NOEVENT;
}

void CPlayer_SSH_Ice::Late_Update()
{
}

void CPlayer_SSH_Ice::Render(HDC hDC)
{
    Ellipse(hDC,
        int(m_tInfo.vPos.x - 100.f),
        int(m_tInfo.vPos.y - 100.f),
        int(m_tInfo.vPos.x + 100.f),
        int(m_tInfo.vPos.y + 100.f));

    Ellipse(hDC,
        int(m_vPoint.x - 20.f),
        int(m_vPoint.y - 20.f),
        int(m_vPoint.x + 20.f),
        int(m_vPoint.y + 20.f));

    TCHAR szStatus[100]{};

    swprintf_s(szStatus, L"얼 각도 : %.2f", m_fAngle);
    TextOut(hDC, 500, 500, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"얼 원의 위치 X : %.2f, Y : %.2f", m_vPoint.x, m_vPoint.y);
    TextOut(hDC, 500, 520, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"얼");
    TextOut(hDC, (int)m_vPoint.x, (int)m_vPoint.y, szStatus, lstrlen(szStatus));
}

void CPlayer_SSH_Ice::Release()
{
}

void CPlayer_SSH_Ice::Key_Input()
{
    if (m_bChange)
    {
        if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
        {
            m_fAngle -= 5.f;
        }
        else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
        {
            m_fAngle += 5.f;
        }
    }
}
