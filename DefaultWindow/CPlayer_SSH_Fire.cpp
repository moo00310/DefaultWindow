#include "pch.h"
#include "CPlayer_SSH_Fire.h"

#include "CAbstractFactory.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CObjMgr.h"

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
    m_bRev = true; // ??繞???濡る룎????怨뺣펺 ???????몃┃?リ옇?↓뇡節덈닱筌뤾쑬???筌뤾퍜??

    m_fAngle = 0.f;

    m_pBitOrbit = CAbstractFactory<CBitOrbit_SSH>::Create({ m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f });
    CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, m_pBitOrbit);
}

int CPlayer_SSH_Fire::Update()
{
    D3DXMATRIX matScale, matRotZ, matTranse, matRevZ, matParrent;

    // ?????곌떠?????怨쀬죯??嶺뚮씭??キ????貫??
    // D3DXMatrixScaling(?롪퍒???쒖쾸沃섅굦諭????繞③뇡???怨쀬죯???낅슣??? X?꾩룄??? Y?꾩룄??? Z?꾩룄???

    // ??????곌떠?????怨쀬죯??嶺뚮씭??キ????貫??
    // D3DXMatrixRotationZ(?롪퍒???쒖쾸沃섅굦諭????繞③뇡???怨쀬죯???낅슣??? ??????띠룄??뙴???怨뺥꺏??)
    // 
    // ?熬곣뫚???곌떠?????怨쀬죯??嶺뚮씭??キ????貫??
    // D3DXMatrixTranslation(?롪퍒???쒖쾸沃섅굦諭????繞③뇡???怨쀬죯???낅슣??? x?熬곣뫚?? y?熬곣뫚?? z?熬곣뫚??

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
        
    //??ㅻ쾴??????륁춺???ㅻ쾴??
    if (m_bRev)
    {
        m_fAngle += m_fRevSpeed;
    }

    //?꾩룆???? ???용┃???좊듆 ??戮곗겱??
    if (!m_bRev)
    {
        D3DXMatrixTranslation(&matParrent, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
        m_pBitOrbit->Set_vPos(m_pTarget->Get_Info().vPos);
    }
    // ?꾩룆?????좊듆 ??濚밸Þ?붷ㅇ?????뿉???ㅻ쾴??
    else if (m_bRev)
    {
        if (CPlayer_SSH* Temp = dynamic_cast<CPlayer_SSH*>(m_pTarget))
        {
            D3DXMatrixTranslation(&matParrent, Temp->Get_vPoint().x, Temp->Get_vPoint().y, 0.f);
            // ??ㅻ쾴???濡レ맪 ?熬곣뫚?????????熬곣뫚??????삳낵繞벿쇨섭????濚밸Þ??????熬곣뫚??繞벿살탳???怨쀬Ŧ ??ㅻ쾴????????덉┣????
            m_tInfo.vPos = Temp->Get_vPoint();
            m_pBitOrbit->Set_vPos(m_tInfo.vPos);
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
