#include "pch.h"
#include "CSpawner.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CSpawner::CSpawner()
	:m_ullLastSpawnTime(0), m_pRightSpawn(nullptr), m_pLeftSpawn(nullptr)
{
}

CSpawner::~CSpawner()
{
	Release();
}

void CSpawner::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
}

int CSpawner::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Check_SpawnTime();

	return OBJ_NOEVENT;
}

void CSpawner::Late_Update()
{
}

void CSpawner::Render(HDC hDC)
{
	TCHAR cBuffer[64]; //저장할 문자열 버퍼

	_stprintf_s(cBuffer, _T("Speed: %.2f"), m_fSpeed);
	TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.3f), cBuffer, (int)_tcslen(cBuffer));

}

void CSpawner::Release()
{
}

void CSpawner::Spawn()
{
	//소환
	m_fSpeed = SPEED_MIN + (rand() % (SPEED_MAX - SPEED_MIN + 1));

	m_pLeftSpawn = CAbstractFactory<CSquare>::Create(-(SIDE * 0.5f), WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pLeftSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pLeftSpawn))
	{
		pSquare->Set_RollLeft(false);
		pSquare->Set_Speed(m_fSpeed);
	}

	m_pRightSpawn = CAbstractFactory<CSquare>::Create(SIDE * 9.5f, WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pRightSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pRightSpawn))
	{
		pSquare->Set_RollLeft(true);
		pSquare->Set_Speed(m_fSpeed);
	}
}

void CSpawner::Check_SpawnTime()
{
	if (m_ullLastSpawnTime + 6000 < GetTickCount64())
	{
		m_ullLastSpawnTime = GetTickCount64();
		Remove_OldSquare();
		Spawn();
	}
}

void CSpawner::Remove_OldSquare()
{
	list<CObj*> LeftList = CObjMgr::Get_Instance()->Get_List()[OBJ_MONSTER];
	list<CObj*> RightList = CObjMgr::Get_Instance()->Get_List()[OBJ_BULLET];

	if (LeftList.size())
	{
		CObj* pLeft = *LeftList.begin();
		if (pLeft)
		{
			pLeft->Set_Dead();
		}
	}
	if (RightList.size())
	{
		CObj* pRight = *RightList.begin();
		if (pRight)
		{
			pRight->Set_Dead();
		}
	}

	//이전 사각형 삭제
	/*if (m_pLeftSpawn)
	{
		m_pLeftSpawn->Set_Dead();
		m_pLeftSpawn = nullptr;
	}
	if (m_pRightSpawn)
	{
		m_pRightSpawn->Set_Dead();
		m_pRightSpawn = nullptr;
	}*/
}
