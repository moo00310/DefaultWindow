#pragma once
#include "CObj.h"

#define SIDE (WINCX/9)
#define SPEED_MIN 2
#define SPEED_MAX 10
#define ROLL_COUNT 6
#define FALL_SPEED 10.f
#define GOUP_SPEED 5.f
#define LERP_SPEED 0.3f

class CSquare :
    public CObj
{
public:
    CSquare();
    virtual ~CSquare();
public:
    void Set_Assembled() { m_bAssembled = true; }
    void Set_RollLeft(bool _b);
    void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
    D3DXVECTOR3 Get_World_Center() { return m_vWorldPoint_Center; }
    void Set_RollTime(ULONGLONG _ullTimeInterval);

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Update_WorldMatrix();
    void Roll_Corners();
    void Roll();
    void Check_ScreenOut();
    bool Wait_Time();
    void Change_Speed();
    void Fall();
    void Go_Up();
    void OnVertexTouch();
    void Check_RollTime();
private:
    //사각형 점 4개
    D3DXVECTOR3 m_arrLocalPoint[4];
    D3DXVECTOR3 m_arrWorldPoint[4];

    D3DXVECTOR3 m_vLocalPoint_Center;
    D3DXVECTOR3 m_vWorldPoint_Center;

    float       m_fAngle;
    //float       m_fSize;
    int         m_iRotPoint;
    bool        m_bRollLeft;
    ULONGLONG   m_ullWaitTime;

    FMOD::Studio::EventInstance* m_pNotePoint;
    FMOD::Studio::Bank* m_pBankPoint;

    int         m_iNote;

    float       m_fCurSpeed;
    float       m_fTime;

    bool        m_bFall;

    ULONGLONG   m_ullNextRollTime;
    ULONGLONG   m_arrRollTime[ROLL_COUNT];
    int         m_iRollCount;

    bool        m_bLerp;
    float       m_fTargetAngle;

    bool        m_bAssembled;

};

