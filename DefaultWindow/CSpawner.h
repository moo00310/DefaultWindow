#pragma once
#include "CObj.h"
class CSpawner :
    public CObj
{
public:
    CSpawner();
    virtual ~CSpawner();
public:
    CObj*   Get_LeftSqure() { return m_pLeftSquare; }
    CObj*   Get_RightSqure() { return m_pRightSquare; }
    void    Set_LeftSquare(CObj* _pObj) { m_pLeftSquare = _pObj; }
    void    Set_RightSquare(CObj* _pObj) { m_pRightSquare = _pObj; }

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

