#pragma once
#include "CScene.h"
class CRhythmWorld :
    public CScene
{
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

