#pragma once
#include "CObj.h"
class CSpawner :
    public CObj
{
public:
    CSpawner();
    virtual ~CSpawner();
public:
    CObj*   Get_LeftSqure() { return m_pRightSpawn; }
    CObj*   Get_RightSqure() { return m_pLeftSpawn; }
    void    Set_LeftSquare(CObj* _pObj) { m_pRightSpawn = _pObj; }
    void    Set_RightSquare(CObj* _pObj) { m_pLeftSpawn = _pObj; }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Spawn();
    void Check_SpawnTime();
    void Remove_OldSquare();
public:
    ULONGLONG   m_ullLastSpawnTime;
    CObj*       m_pRightSpawn;
    CObj*       m_pLeftSpawn;
};

