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
    m_bRev = true; // ??以??섎굹???쇰떒 ?뚯븘?쇳븯湲곕븣臾몄뿉 ?몃（
}

int CPlayer_SSH_Fire::Update()
{
    D3DXMATRIX matScale, matRotZ, matTranse, matRevZ, matParrent;

    // ?ш린 蹂???됰젹??留뚮뱶???⑥닔
    // D3DXMatrixScaling(寃곌낵媛믪쓣 ??ν븷 ?됰젹??二쇱냼, X諛곗쑉, Y諛곗쑉, Z諛곗쑉)

    // ?뚯쟾 蹂???됰젹??留뚮뱶???⑥닔
    // D3DXMatrixRotationZ(寃곌낵媛믪쓣 ??ν븷 ?됰젹??二쇱냼, ?뚯쟾 媛곷룄(?쇰뵒??)
    // 
    // ?꾩튂 蹂???됰젹??留뚮뱶???⑥닔
    // D3DXMatrixTranslation(寃곌낵媛믪쓣 ??ν븷 ?됰젹??二쇱냼, x?꾩튂, y?꾩튂, z?꾩튂)

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
    D3DXMatrixTranslation(&matTranse, -50.f, 0.f, 0.f);
    D3DXMatrixRotationZ(&matRevZ, D3DXToRadian(m_fAngle));

    if (m_fAngle > m_fMaxAngle)
    {
        m_fAngle -= m_fAngle;
        m_iRevCount++;
    }
        

    //怨듭쟾?대씪硫?怨듭쟾
    if (m_bRev)
    {
        m_fAngle += m_fRevSpeed;
    }

    //諛붾뚯? ?딆븯?ㅻ㈃ ?쒖옄由?
    if (!m_bRev)
    {
        D3DXMatrixTranslation(&matParrent, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
    }
    // 諛붽펷?ㅻ㈃ ?源껋쨷?ъ쑝濡?怨듭쟾
    else if (m_bRev)
    {
        if (CPlayer_SSH* Temp = dynamic_cast<CPlayer_SSH*>(m_pTarget))
        {
            D3DXMatrixTranslation(&matParrent, Temp->Get_vPoint().x, Temp->Get_vPoint().y, 0.f);
            // 怨듭쟾?섎뜕 ?꾩튂瑜??먮옒 ?꾩튂???섍꺼以섏꽌 ?源껋씠 洹??꾩튂 以묒떖?쇰줈 怨듭쟾?????덈룄濡???
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
    if (m_bDead)
        return;

    int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    Ellipse(hDC,
        int(m_vPoint.x - 20.f + iScrollX),
        int(m_vPoint.y - 20.f + iScrollY),
        int(m_vPoint.x + 20.f + iScrollX),
        int(m_vPoint.y + 20.f + iScrollY));

    TCHAR szStatus[100]{};

    swprintf_s(szStatus, L"Fire's Angle : %.2f", m_fAngle);
    TextOut(hDC, 500, 20, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"Fire's Location X : %.2f, Y : %.2f", m_vPoint.x, m_vPoint.y);
    TextOut(hDC, 500, 40, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"Fire");
    TextOut(hDC, (int)m_vPoint.x + iScrollX, (int)m_vPoint.y + iScrollY, szStatus, lstrlen(szStatus));
    swprintf_s(szStatus, L"Fire's RevCount : %d", m_iRevCount);
    TextOut(hDC, 500, 60, szStatus, lstrlen(szStatus));
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
