#include "pch.h"
#include "CPlayer_SSH_Fire.h"

#include "CKeyMgr.h"
#include "CScrollMgr.h"

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
    m_bRev = true; // ??餓???롪돌????곕뼊 ???툡??노릭疫꿸퀡釉ｈ눧紐꾨퓠 ?紐껓펷

    m_fAngle = 0.f;
}

int CPlayer_SSH_Fire::Update()
{
    D3DXMATRIX matScale, matRotZ, matTranse, matRevZ, matParrent;

    // ??由?癰궰????곗졊??筌띾슢諭????λ땾
    // D3DXMatrixScaling(野껉퀗?드첎誘れ뱽 ???館釉???곗졊??雅뚯눘?? X獄쏄퀣?? Y獄쏄퀣?? Z獄쏄퀣??

    // ???읈 癰궰????곗졊??筌띾슢諭????λ땾
    // D3DXMatrixRotationZ(野껉퀗?드첎誘れ뱽 ???館釉???곗졊??雅뚯눘?? ???읈 揶쏄낮猷???곕탵??)
    // 
    // ?袁⑺뒄 癰궰????곗졊??筌띾슢諭????λ땾
    // D3DXMatrixTranslation(野껉퀗?드첎誘れ뱽 ???館釉???곗졊??雅뚯눘?? x?袁⑺뒄, y?袁⑺뒄, z?袁⑺뒄)

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
    D3DXMatrixTranslation(&matTranse, -50.f, 0.f, 0.f);
    D3DXMatrixRotationZ(&matRevZ, D3DXToRadian(m_fAngle));

    if (m_fAngle > m_fMaxAngle)
    {
        m_fAngle -= m_fAngle;
        if(m_bStart && !m_bEnd)
            m_iRevCount++;
    }
        
    //?⑤벊????わ쭖??⑤벊??
    if (m_bRev)
    {
        m_fAngle += m_fRevSpeed;
    }

    //獄쏅뗀??? ??녿릭??삠늺 ??뽰쁽??
    if (!m_bRev)
    {
        D3DXMatrixTranslation(&matParrent, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
    }
    // 獄쏅떽???삠늺 ??繹먭퍔夷???앮에??⑤벊??
    else if (m_bRev)
    {
        if (CPlayer_SSH* Temp = dynamic_cast<CPlayer_SSH*>(m_pTarget))
        {
            D3DXMatrixTranslation(&matParrent, Temp->Get_vPoint().x, Temp->Get_vPoint().y, 0.f);
            // ?⑤벊???롫쐲 ?袁⑺뒄???癒?삋 ?袁⑺뒄????띻볼餓μ꼷苑???繹먭퍔??域??袁⑺뒄 餓λ쵐???곗쨮 ?⑤벊???????덈즲嚥???
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
    if (1 <= m_iRevCount)
        m_bDead = true;
}

void CPlayer_SSH_Fire::Render(HDC hDC)
{
    if (m_bDead)
        return;

    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    DEFINE_DRAWTOOL;
    NEW_DRAWTOOL(PS_SOLID, 1, RGB(255,0,0), RGB(255,0,0));

    Ellipse(hDC,
        int(m_vPoint.x - 20.f + iScrollX),
        int(m_vPoint.y - 20.f + iScrollY),
        int(m_vPoint.x + 20.f + iScrollX),
        int(m_vPoint.y + 20.f + iScrollY));

    DELETE_DRAWTOOL;

    TCHAR szStatus[100]{};

    swprintf_s(szStatus, L"Fire's Angle : %.2f", m_fAngle);
    TextOut(hDC, 500, 20, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"Fire's Location X : %.2f, Y : %.2f", m_vPoint.x, m_vPoint.y);
    TextOut(hDC, 500, 40, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"Fire's RevCount : %d", m_iRevCount);
    TextOut(hDC, 500, 60, szStatus, lstrlen(szStatus));
    switch (m_bStart)
    {
    case true:
        swprintf_s(szStatus, L"Start");
        TextOut(hDC, 500, 80, szStatus, lstrlen(szStatus));
        break;

    case false:
        swprintf_s(szStatus, L"False");
        TextOut(hDC, 500, 80, szStatus, lstrlen(szStatus));
        break;
    }

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
