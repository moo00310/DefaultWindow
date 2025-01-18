#pragma once
#include "CObj.h"

#define SPAWN_COUNT 30

struct tagSpawnInfo
{
    ULONGLONG   ullSpawnTime;
    float       fSpeed;
}typedef SPAWN_INFO;

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
    void Spawn(float _fSpeed);
    void Check_SpawnTime();
    void Remove_OldSquare();
    void Set_SpawnTime();
public:
    ULONGLONG   m_ullLastSpawnTime;
    ULONGLONG   m_ullStartTime;
    ULONGLONG   m_ullNextSpawnTime;
    ULONGLONG   m_arrSpawnTime[SPAWN_COUNT];
    SPAWN_INFO  m_arrSpawnInfo[SPAWN_COUNT];
    int         m_iSpawnIndex;

    CObj*       m_pRightSpawn;
    CObj*       m_pLeftSpawn;
    
};

