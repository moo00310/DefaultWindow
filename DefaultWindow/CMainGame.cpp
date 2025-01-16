#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"

CMainGame::CMainGame():  m_longTime(GetTickCount64()), m_iFPS(0), m_hDC(nullptr), m_hBit(nullptr), m_memDC(nullptr)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_hBit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_memDC = CreateCompatibleDC(m_hDC);
	SelectObject(m_memDC, m_hBit);

	CSceneMgr::Get_Instance()->Set_Scene(SC_MOO);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	CCameraMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	ShowFps();
	Rectangle(m_memDC, 0,0, WINCX, WINCY);

	CSceneMgr::Get_Instance()->Render(m_memDC);
	CCameraMgr::Get_Instance()->Render(m_hDC, m_memDC);
}

void CMainGame::Release()
{
	CKeyMgr::Destroy_Instance();
	CObjMgr::DestroyInstance();
	CSceneMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CCameraMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::ShowFps()
{
	++m_iFPS;

	if (m_longTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_longTime = GetTickCount64();
	}
}
