#pragma once
#include "CObj.h"
class CSquare :
    public CObj
{
public:
    CSquare();
    virtual ~CSquare();
public:
    void Initialize() override;
    int Update() override;
    void Update_WorldMatrix();
    void Render(HDC hDC) override;
    void Release() override;
private:
    //사각형 점 4개
    D3DXVECTOR3 m_vLocalPoint[4];
    D3DXVECTOR3 m_vWorldPoint[4];

    D3DXVECTOR3 m_vLocalPoint_Center;
    D3DXVECTOR3 m_vWorldPoint_Center;

    float       m_fAngle;
    float       m_fSize;
    int         m_iRotPoint;

    // CObj을(를) 통해 상속됨
    void Late_Update() override;
};

