#pragma once
#include "CObj.h"

#define SPAWN_COUNT 50
#define BEAT_4 650 //정박 4분의 4박자
#define BEAT_3 (ULONGLONG)((float)BEAT_4 * (3.f / 4.f)) // 4분의 3박자
#define BEAT_2 (ULONGLONG)((float)BEAT_4 * (2.f / 4.f)) // 4분의 2박자
#define BEAT_1 (ULONGLONG)((float)BEAT_4 * (7.f / 16.f)) // 4분의 1박자

struct tagSpawnInfo
{
    ULONGLONG   ullSpawnTime;
    ULONGLONG   ullTimeInterval;
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
    void Spawn(ULONGLONG _ullTimeInterval);
    void Check_SpawnTime();
    void Remove_OldSquare();
    void Set_SpawnTime();
    void Set_SpawnInfo(int _iIndex, ULONGLONG _ullSpawnTime, ULONGLONG _ullTimeInterval);
public:
    ULONGLONG   m_ullLastSpawnTime;
    ULONGLONG   m_ullStartTime;
    ULONGLONG   m_ullNextSpawnTime;
    //ULONGLONG   m_arrSpawnTime[SPAWN_COUNT];
    SPAWN_INFO  m_arrSpawnInfo[SPAWN_COUNT];
    int         m_iSpawnIndex;

    CObj*       m_pRightSpawn;
    CObj*       m_pLeftSpawn;
    
};

