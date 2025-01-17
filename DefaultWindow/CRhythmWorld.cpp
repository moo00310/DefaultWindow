#include "pch.h"
#include "CRhythmWorld.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CRhythmWorld::CRhythmWorld()
{
}

CRhythmWorld::~CRhythmWorld()
{
    Release();
}

void CRhythmWorld::Initialize()
{
    CObj* pObj(nullptr);
    pObj = CAbstractFactory<CSquare>::Create(SIDE * 2.f, WINCY * 0.5f - SIDE * 0.5f);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);

    pObj = CAbstractFactory<CSquare>::Create(SIDE * ((int)(WINCX / SIDE) - 1), WINCY * 0.5f - SIDE * 0.5f);
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);
    if (CSquare* pSquare = dynamic_cast<CSquare*>(pObj))
    {
        pSquare->Set_RollLeft(true);
    }
}

int CRhythmWorld::Update()
{
    CObjMgr::Get_Instance()->Update();
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

    CObjMgr::Get_Instance()->Render(hDC);
}

void CRhythmWorld::Release()
{
    CObjMgr::DestroyInstance();
}
