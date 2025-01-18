#include "pch.h"
#include "CPlayer_SSH.h"

#include "CKeyMgr.h"
#include "CscrollMgr.h"

CPlayer_SSH::CPlayer_SSH() 
	: m_bRev(false), m_fMaxAngle(360.f), m_fRevSpeed(REV_SPEED), m_iRevCount(0)
{
}

CPlayer_SSH::~CPlayer_SSH()
{
}
