#include "pch.h"
#include "CSpawner.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CSpawner::CSpawner()
	:m_ullLastSpawnTime(0), m_pRightSpawn(nullptr), m_pLeftSpawn(nullptr), m_ullStartTime(0), m_ullNextSpawnTime(0), m_iSpawnIndex(0)
{
	//ZeroMemory(&m_arrSpawnTime, sizeof(m_arrSpawnTime));
	ZeroMemory(&m_arrSpawnInfo, sizeof(m_arrSpawnInfo));
}

CSpawner::~CSpawner()
{
	Release();
}

void CSpawner::Initialize()
{
	Set_SpawnTime();

	m_eRender = RENDER_GAMEOBJECT;

	m_ullStartTime = GetTickCount64();

	m_ullNextSpawnTime = m_arrSpawnInfo[0].ullSpawnTime;
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

	//_stprintf_s(cBuffer, _T("Speed: %.2f"), m_fSpeed);
	//TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.3f), cBuffer, (int)_tcslen(cBuffer));

	_stprintf_s(cBuffer, _T("Spawn Index: %d"), m_iSpawnIndex - 1);
	TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.3f), cBuffer, (int)_tcslen(cBuffer));

}

void CSpawner::Release()
{
}

void CSpawner::Spawn()
{
	//소환
	m_fSpeed = 4.f;//SPEED_MIN + (rand() % (SPEED_MAX - SPEED_MIN + 1));

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

void CSpawner::Spawn(ULONGLONG _ullTimeInterval)
{
	//소환
	//m_fSpeed = _fSpeed;//SPEED_MIN + (rand() % (SPEED_MAX - SPEED_MIN + 1));

	m_pLeftSpawn = CAbstractFactory<CSquare>::Create(-(SIDE * 0.5f), WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pLeftSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pLeftSpawn))
	{
		pSquare->Set_RollLeft(false);
		//pSquare->Set_Speed(m_fSpeed);
		pSquare->Set_RollTime(_ullTimeInterval);
	}

	m_pRightSpawn = CAbstractFactory<CSquare>::Create(SIDE * 9.5f, WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pRightSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pRightSpawn))
	{
		pSquare->Set_RollLeft(true);
		//pSquare->Set_Speed(m_fSpeed);
		pSquare->Set_RollTime(_ullTimeInterval);
	}
}

void CSpawner::Check_SpawnTime()
{
	if (m_ullStartTime + m_ullNextSpawnTime < GetTickCount64())
	{
		Spawn(m_arrSpawnInfo[m_iSpawnIndex].ullTimeInterval);
		m_ullNextSpawnTime = m_arrSpawnInfo[++m_iSpawnIndex].ullSpawnTime;

	}

	//if (m_ullLastSpawnTime + 5000 < GetTickCount64())
	//{
	//	m_ullLastSpawnTime = GetTickCount64();
	//	//Remove_OldSquare();
	//	Spawn();
	//}
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

void CSpawner::Set_SpawnTime()
{
	for (int i = 0; i < SPAWN_COUNT; ++i)
	{
		m_arrSpawnInfo[i].ullSpawnTime = m_ullStartTime + 5000 * (i + 1);
		m_arrSpawnInfo[i].ullTimeInterval = BEAT_2;
	}

	Set_SpawnInfo(0, 5000, BEAT_3);
	Set_SpawnInfo(1, 10000, BEAT_4);
	Set_SpawnInfo(2, 15000, BEAT_3);
	Set_SpawnInfo(3, 19500, BEAT_3);
	Set_SpawnInfo(4, 22000, BEAT_2);
	Set_SpawnInfo(5, 24500, BEAT_3);
	//여기서 좀 밀리는 느낌
	Set_SpawnInfo(6, 29500, BEAT_4);
	Set_SpawnInfo(7, 34500, BEAT_3);
	Set_SpawnInfo(8, 39500, BEAT_3);
	Set_SpawnInfo(9, 42000, BEAT_2);
	//빨라지는 부분
	ULONGLONG ullStart = 49000;
	ULONGLONG ullInterval = 1600;
	Set_SpawnInfo(10, 49000, BEAT_2);
	Set_SpawnInfo(11, 50700, BEAT_2);
	Set_SpawnInfo(12, 52400, BEAT_2);
	Set_SpawnInfo(13, 54100, BEAT_1);//1700

	Set_SpawnInfo(14, 55900, BEAT_2);
	Set_SpawnInfo(15, 57600, BEAT_2);
	Set_SpawnInfo(16, 59300, BEAT_2);
	Set_SpawnInfo(17, 61000, BEAT_1);//1700

	//여기서 다시 느려짐
	Set_SpawnInfo(18, 62600, BEAT_2);
	Set_SpawnInfo(19, 67500, BEAT_4);
	Set_SpawnInfo(20, 66000, BEAT_2);
	Set_SpawnInfo(21, 67700, BEAT_1);//1700


}

void CSpawner::Set_SpawnInfo(int _iIndex, ULONGLONG _ullSpawnTime, ULONGLONG _ullTimeInterval)
{
	m_arrSpawnInfo[_iIndex].ullSpawnTime = m_ullStartTime + _ullSpawnTime;
	m_arrSpawnInfo[_iIndex].ullTimeInterval = _ullTimeInterval;
}
