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
    CObj* pObj = CAbstractFactory<CSquare>::Create();
    CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, pObj);

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
