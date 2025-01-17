#pragma once
#include "CObj.h"

#define SIDE (WINCX/12)

class CSquare :
    public CObj
{
public:
    void Set_RollLeft(bool _b) { m_bLeft = _b; }
    D3DXVECTOR3 Get_World_Center() { return m_vWorldPoint_Center; }
public:
    CSquare();
    virtual ~CSquare();
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
private:
    //사각형 점 4개
    D3DXVECTOR3 m_vLocalPoint[4];
    D3DXVECTOR3 m_vWorldPoint[4];

    D3DXVECTOR3 m_vLocalPoint_Center;
    D3DXVECTOR3 m_vWorldPoint_Center;

    float       m_fAngle;
    float       m_fSize;
    int         m_iRotPoint;
    bool        m_bLeft;

};

