#pragma once
#include "CObj.h"

#define STICK_WIDTH 30
#define STICK_HEIGHT 100

#define PULL_LENGTH 100.0f // 뒤로 당기는 길이를 정의
#define FLY_SPEED 100.f

#define JUDGE_WINDOW 100.f
#define FLY_INTERVAL 500

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
    void Set_OriginPosition();
    void Set_BackPosition();
    void Fly();
    void Check_ScreenOut();
    void Check_Hit();
    void Assemble_Parts();
    void Check_ResetPosition();
private:
    //사각형 점 4개
    D3DXVECTOR3 m_arrLocalPoint[4];
    D3DXVECTOR3 m_arrWorldPoint[4];

    //최초 위치
    D3DXVECTOR3 m_vOriginPosition;

    //후퇴 위치
    D3DXVECTOR3 m_vLocalBackPosition;
    D3DXVECTOR3 m_vWorldBackPosition;

    //발사여부
    bool        m_bFly;
    float       m_fDistance;
    int         m_iScore;
    
    //발사한 시간
    ULONGLONG   m_ullLastFlyTime;
};

