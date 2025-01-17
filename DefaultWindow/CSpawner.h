#pragma once
#include "CObj.h"
class CSpawner :
    public CObj
{
public:
    CSpawner();
    virtual ~CSpawner();
public:
    CObj* Get_LeftSqure() { return m_pLeftSquare; }
    CObj* Get_RightSqure() { return m_pRightSquare; }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Spawn();
public:
    ULONGLONG   m_ullLastSpawnTime;
    CObj*       m_pLeftSquare;
    CObj*       m_pRightSquare;
};

