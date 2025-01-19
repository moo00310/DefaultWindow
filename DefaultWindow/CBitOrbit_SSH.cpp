#include "pch.h"
#include "CBitOrbit_SSH.h"

#include "CPlayer_SSH_Fire.h"
#include "CPlayer_SSH_Ice.h"

#include "CScrollMgr.h"
#include "CObjMgr.h"

CBitOrbit_SSH::CBitOrbit_SSH() : m_fMaxScale(50.f)
{
    ZeroMemory(&m_fScale, sizeof(m_fScale));
}

CBitOrbit_SSH::~CBitOrbit_SSH()
{
}

void CBitOrbit_SSH::Initialize()
{
    m_eRender = RENDER_EFFECT;

    m_vPoint = { 0.f, 0.f, 0.f };
    m_vOriginPoint = m_vPoint;
    m_fSpeed = 3.f;
}

int CBitOrbit_SSH::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    
    m_fAngle += 5.f;

    D3DXMATRIX matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    m_vPoint = m_vOriginPoint;
    D3DXVec3TransformCoord(&m_vPoint, &m_vPoint, &m_tInfo.matWorld);

    return OBJ_NOEVENT;
}

void CBitOrbit_SSH::Late_Update()
{
    if (SSH_FIRE->Get_bRev())
    {
        m_fScale[PT_FIRE] += m_fSpeed;
        m_fScale[PT_ICE] -= m_fSpeed;

        if (m_fMaxScale <= m_fScale[PT_FIRE])
            m_fScale[PT_FIRE] = m_fMaxScale;

        if (0 >= m_fScale[PT_ICE])
            m_fScale[PT_ICE] = 0.f;
    }
    else if (SSH_ICE->Get_bRev())
    {
        m_fScale[PT_FIRE] -= m_fSpeed;
        m_fScale[PT_ICE] += m_fSpeed;

        if (m_fMaxScale <= m_fScale[PT_ICE])
            m_fScale[PT_ICE] = m_fMaxScale;

        if (0 >= m_fScale[PT_FIRE])
            m_fScale[PT_FIRE] = 0.f;
    }
}

void CBitOrbit_SSH::Render(HDC hDC)
{
    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HPEN NewPen;

    if (SSH_FIRE->Get_bRev())
    {
        NewPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
    }
    else if (SSH_ICE->Get_bRev())
    {
        NewPen = CreatePen(PS_DASH, 1, RGB(0, 0, 255));
    }
    else
        NewPen = CreatePen(PS_DASH, 1, RGB(0, 255, 0));
       


    HPEN OldPen = (HPEN)SelectObject(hDC, NewPen);
    HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));

    if (SSH_FIRE->Get_bRev())
    {
        Ellipse(hDC,
            int(m_vPoint.x - m_fScale[PT_FIRE] + iScrollX),
            int(m_vPoint.y - m_fScale[PT_FIRE] + iScrollY),
            int(m_vPoint.x + m_fScale[PT_FIRE] + iScrollX),
            int(m_vPoint.y + m_fScale[PT_FIRE] + iScrollY));
    }

    if (SSH_ICE->Get_bRev())
    {
        Ellipse(hDC,
            int(m_vPoint.x - m_fScale[PT_ICE] + iScrollX),
            int(m_vPoint.y - m_fScale[PT_ICE] + iScrollY),
            int(m_vPoint.x + m_fScale[PT_ICE] + iScrollX),
            int(m_vPoint.y + m_fScale[PT_ICE] + iScrollY));
    }

    SelectObject(hDC, OldPen);
    SelectObject(hDC, OldBrush);
    DeleteObject(NewPen);
    DeleteObject(OldPen);
}

void CBitOrbit_SSH::Release()
{
}
