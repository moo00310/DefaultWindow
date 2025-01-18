#pragma once
#include "CScene.h"
#include "CSpawner.h"

class CRhythmWorld :
    public CScene
{
public:
    CRhythmWorld();
    virtual ~CRhythmWorld();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void    Check_Hit();
private:
    CObj* m_pSpawner;
    float m_fDistance;
    int   m_iScore;
};

