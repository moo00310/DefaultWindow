#include "pch.h"
#include "CCameraMgr.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

void CCameraMgr::Update()
{

}

void CCameraMgr::Render(HDC _hDc, HDC _memDC)
{
	GdiTransparentBlt(_hDc,
		0, 0, WINCX, WINCY, // �����̵�  left/top�� ������
		_memDC,
		0, 0, WINCX, WINCY, // Ȯ���� left/top�� ������
		RGB(0, 2, 0));

	// ���� �Լ�
	//StretchBlt(_hDc,0, 0, WINCX, WINCY, _memDC, WINCX - 1, 0, -WINCX, WINCY, SRCCOPY);
}
