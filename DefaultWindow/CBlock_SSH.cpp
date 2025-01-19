#include "pch.h"
#include "CBlock_SSH.h"

#include "CPlayer_SSH_Fire.h"
#include "CPlayer_SSH_Ice.h"

#include "CScrollMgr.h"
#include "CObjMgr.h"

CBlock_SSH::CBlock_SSH() : m_bSlow(false)
{
}

CBlock_SSH::~CBlock_SSH()
{
}

void CBlock_SSH::Initialize()
{
    D3DXMatrixIdentity(&m_tInfo.matWorld);

    m_vPoint[0] = { -25.f, -25.f, 0.f };
    m_vPoint[1] = {  25.f, -25.f, 0.f };
    m_vPoint[2] = {  25.f,  25.f, 0.f };
    m_vPoint[3] = { -25.f,  25.f, 0.f };

    for (int i = 0; i < 4; i++)
        m_vOriginPoint[i] = m_vPoint[i];

    m_eRender = RENDER_GAMEOBJECT;
}

int CBlock_SSH::Update()
{
    D3DXMATRIX matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + CScrollMgr::Get_Instance()->Get_ScrollX(), m_tInfo.vPos.y + CScrollMgr::Get_Instance()->Get_ScrollY(), m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; i++)
    {
        m_vPoint[i] = m_vOriginPoint[i];
        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
    }

    return OBJ_NOEVENT;
}

void CBlock_SSH::Late_Update()
{
}

void CBlock_SSH::Render(HDC hDC)
{
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 4; i++)
    {
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
    }
    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CBlock_SSH::Release()
{
}
