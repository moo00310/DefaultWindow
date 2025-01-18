#pragma once
#include "CObj.h"

#define STICK_WIDTH 10
#define STICK_HEIGHT 50

#define PULL_LENGTH 10.0f // 뒤로 당기는 길이를 정의
#define FLY_SPEED 50.f

class CStick :
    public CObj
{
public:
    CStick();
    virtual ~CStick();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Update_WorldMatrix();
    void Input_Key();
    void Set_BackPosition();
    void Fly();
private:
    //사각형 점 4개
    D3DXVECTOR3 m_arrLocalPoint[4];
    D3DXVECTOR3 m_arrWorldPoint[4];

    //후퇴 위치
    D3DXVECTOR3 m_vLocalBackPosition;
    D3DXVECTOR3 m_vWorldBackPosition;

    //발사여부
    bool        m_bFly;
};

