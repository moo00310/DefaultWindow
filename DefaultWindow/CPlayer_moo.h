#pragma once
#include "CPlayer.h"

class CPlayer_moo : public CPlayer
{
public:
    CPlayer_moo();
    ~CPlayer_moo();

public:
    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Key_Input() override;

private:
    float m_Diagonal;


    // CPlayer��(��) ���� ��ӵ�
    void Late_Update() override;

};

