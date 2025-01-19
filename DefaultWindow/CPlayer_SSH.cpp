#include "pch.h"
#include "CPlayer_SSH.h"

#include "CKeyMgr.h"
#include "CscrollMgr.h"

CPlayer_SSH::CPlayer_SSH() 
	: m_bRev(false), m_fMaxAngle(360.f), m_fRevSpeed(REV_SPEED),
	m_iRevCount(0), m_bStart(false), m_bEnd(false), m_pBitOrbit(nullptr)
{
}

CPlayer_SSH::~CPlayer_SSH()
{
}
