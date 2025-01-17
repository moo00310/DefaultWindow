#include "pch.h"
#include "CCameraMgr.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

void CCameraMgr::Update()
{

}

void CCameraMgr::Render(HDC _hDc, HDC _memDC)
{
	GdiTransparentBlt(_hDc,
		0, 0, WINCX, WINCY, // 평행이동  left/top과 스케일
		_memDC,
		0, 0, WINCX, WINCY, // 확대할 left/top과 스케일
		RGB(0, 2, 0));

	// 반전 함수
	//StretchBlt(_hDc,0, 0, WINCX, WINCY, _memDC, WINCX - 1, 0, -WINCX, WINCY, SRCCOPY);
}
