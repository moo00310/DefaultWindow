#include "pch.h"
#include "CRhythmWorld.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CSpawner.h"
#include "CSoundMgr.h"

CRhythmWorld::CRhythmWorld()
    :m_pSpawner(nullptr), m_fDistance(0.f)
{
}

CRhythmWorld::~CRhythmWorld()
{
    Release();
}

void CRhythmWorld::Initialize()
{
    CSoundMgr::Get_Instance()->Initialize();

    m_pSpawner = CAbstractFactory<CSpawner>::Create();
    CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, m_pSpawner);

}

int CRhythmWorld::Update()
{
    CObjMgr::Get_Instance()->Update();
    return 0;
}

void CRhythmWorld::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();

    Check_Hit();

    CKeyMgr::Get_Instance()->Update();

}

void CRhythmWorld::Render(HDC hDC)
{
    MoveToEx(hDC, 0, int(WINCY * 0.5f), nullptr);
    LineTo(hDC, int(WINCX), int(WINCY * 0.5f));

    TCHAR cBuffer[64]; //저장할 문자열 버퍼

    _stprintf_s(cBuffer, _T("Distance: %.2f"), m_fDistance);
    TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.35f), cBuffer, (int)_tcslen(cBuffer));

    CObjMgr::Get_Instance()->Render(hDC);
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
        }
    }
}
