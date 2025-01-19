#pragma once

#include "CObj.h"
#include "CBlock_SSH.h"
#include "CMemoryPoolMgr.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(D3DXVECTOR3 _vPos, float _fAngle = 180.f)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_vPos(_vPos);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

