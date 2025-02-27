#include "pch.h"
#include "CObjMgr.h"
#include "CThorn.h"
#include "CMemoryPoolMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr() : m_pPlayer(nullptr)
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pDst)
{
	/*if (m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float	fDistance(0.f);

	for (auto& Src : m_ObjList[eID])
	{
		if (Src->Get_Dead())
			continue;

		float		fWidth = abs(pDst->Get_Info().fX - Src->Get_Info().fX);
		float		fHeight = abs(pDst->Get_Info().fY - Src->Get_Info().fY);

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Src;
			fDistance = fDiagonal;
		}
	}	*/	

	return nullptr;
}

bool CObjMgr::Collision_Check(OBJID _eID, float _Dst, float _Src)
{
	m_pPlayer = m_ObjList[OBJ_PLAYER].front();
	float fRadius = (_Dst + _Src) * 0.5f;

	for (CObj* obj : m_ObjList[_eID]) {
		float fWidth = abs(m_pPlayer->Get_Info().vPos.x - obj->Get_Info().vPos.x);
		float fHeight = abs(m_pPlayer->Get_Info().vPos.y - obj->Get_Info().vPos.y);
		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fRadius >= fDiagonal)
			return true; 
	}

	return false;
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if (i == OBJ_MOUSE)
				{
					CMemoryPoolMgr::Get_Instance()->deallocate(*iter);
				}
				else
				{
					Safe_Delete<CObj*>(*iter);
				}
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID	eID = pObj->Get_GroupID();
			m_RenderList[eID].push_back(pObj);
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for (auto& pObj : m_RenderList[i])
			pObj->Render(hDC);

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (i == OBJ_MOUSE)
		{
			for_each(m_ObjList[OBJ_MOUSE].begin(), m_ObjList[OBJ_MOUSE].end(), [](CObj* _obj)
				{
					CMemoryPoolMgr::Get_Instance()->deallocate(_obj);
				});
			m_ObjList[i].clear();
		}
		else
		{
			for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
			m_ObjList[i].clear();
		}
	}
	
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}

void CObjMgr::Dead_Thorn(Direction eID)
{
	for_each(m_ObjList[OBJ_MOUSE].begin(), m_ObjList[OBJ_MOUSE].end(), [=](CObj* monster)
		{
			if(static_cast<CThorn*>(monster)->GetDir() == eID)
				monster->Set_Dead();
		});
}
