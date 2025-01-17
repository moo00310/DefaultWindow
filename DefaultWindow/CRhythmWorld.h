#pragma once
#include "CScene.h"
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
};

