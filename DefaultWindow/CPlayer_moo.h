#pragma once
#include "CPlayer.h"

class CPlayer_moo : public CPlayer
{
public:
    CPlayer_moo();
    ~CPlayer_moo();

public:
    void Initialize() override;
    void Late_Update() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Key_Input() override;

private:
    float m_Diagonal;
    D3DXVECTOR3     m_vOriginPoint;
};

