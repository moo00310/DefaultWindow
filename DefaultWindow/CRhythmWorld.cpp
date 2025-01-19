#include "pch.h"
#include "CRhythmWorld.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CSpawner.h"
#include "CSoundMgr.h"
#include "CStick.h"

CRhythmWorld::CRhythmWorld()
    :m_pSpawner(nullptr), m_fDistance(0.f), m_iScore(0)
{
}

CRhythmWorld::~CRhythmWorld()
{
    Release();
}

void CRhythmWorld::Initialize()
{
    CSoundMgr::Get_Instance()->Initialize();
    CSoundMgr::Get_Instance()->PlayEvent("event:/0004 BGM_DOREMI");
    //CSoundMgr::Get_Instance()->PlayEvent("event:/Tobu & Itro - Sunburst");

    m_pSpawner = CAbstractFactory<CSpawner>::Create();
    CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, m_pSpawner);

    CObj* pObj(nullptr);
    pObj = CAbstractFactory<CStick>::Create(WINCX * 0.5f, WINCY * 0.7f);
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj);
}

int CRhythmWorld::Update()
{
    CObjMgr::Get_Instance()->Update();
    //Check_Hit();
    CKeyMgr::Get_Instance()->Update();

    return 0;
}

void CRhythmWorld::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
}

void CRhythmWorld::Render(HDC hDC)
{
    MoveToEx(hDC, 0, int(WINCY * 0.5f), nullptr);
    LineTo(hDC, int(WINCX), int(WINCY * 0.5f));

    //TCHAR cBuffer[64]; //저장할 문자열 버퍼

    //_stprintf_s(cBuffer, _T("Distance: %.2f"), m_fDistance);
    //TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.35f), cBuffer, (int)_tcslen(cBuffer));

    //_stprintf_s(cBuffer, _T("Score: %d"), m_iScore);
    //TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.15f), cBuffer, (int)_tcslen(cBuffer));

    CObjMgr::Get_Instance()->Render(hDC);

    Draw_Outline(hDC);
}

void CRhythmWorld::Release()
{
    CObjMgr::DestroyInstance();
    CKeyMgr::Destroy_Instance();
    CSoundMgr::Destroy_Instance();
}

void CRhythmWorld::Check_Hit()
{
    if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
    {
        //list<CObj*> SquareList = CObjMgr::Get_Instance()->Get_List()[OBJ_MONSTER];
        //
        //CObj* Square1 = *SquareList.begin();
        //CObj* Square1 = *SquareList.(begin() + 1);

        //
        if (CSpawner* pSpawner = dynamic_cast<CSpawner*>(m_pSpawner))
        {
            CObj* pLeft = pSpawner->Get_LeftSqure();
            CObj* pRight = pSpawner->Get_RightSqure();

            if (!pLeft || !pRight)
            {
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

            if (m_fDistance < 10.f)
            {
                ++m_iScore;
            }
        }
    }
}

void CRhythmWorld::Draw_Outline(HDC hDC)
{
    HPEN hPen = CreatePen(PS_SOLID, 150, RGB(0, 255, 0));
    HGDIOBJ oldPen = SelectObject(hDC, hPen);

    // 화면 테두리 그리기
    MoveToEx(hDC, 0, 0, NULL);           // 왼쪽 상단으로 이동
    LineTo(hDC, WINCX, 0);               // 위쪽 테두리
    LineTo(hDC, WINCX, WINCY);           // 오른쪽 테두리
    LineTo(hDC, 0, WINCY);               // 아래쪽 테두리
    LineTo(hDC, 0, 0);                   // 왼쪽 테두리 (원점으로 돌아감)

    SelectObject(hDC, oldPen);
    DeleteObject(hPen);
}
