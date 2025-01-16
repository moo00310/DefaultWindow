#pragma once
#include "CObj.h"

class CPlayer :  public CObj
{
public:
    CPlayer() {}
    virtual ~CPlayer() {}
     
public:
    void Initialize() PURE;
    int Update() PURE;
    void Late_Update() PURE;
    void Render(HDC hDC) PURE;
    void Release() PURE;
    virtual  void Key_Input() PURE;
};

