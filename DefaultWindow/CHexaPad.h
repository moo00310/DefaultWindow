#pragma once
#include "CObj.h"
#include "CKDHPlayer.h"
#include "Define.h"

class CHexaPad : public CObj
{
public:
	CHexaPad();
	virtual ~CHexaPad();

	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void SetPlayer(CKDHPlayer* _player);
	void SetDirection(kDIRECTION _kDIR);

private:
	float GetDistance(D3DXVECTOR3 _info)
	{
		D3DXVECTOR3 result = { m_localPosition.x - _info.x,  m_localPosition.y - _info.y, m_localPosition.z - _info.z };

		return sqrtf((result.x * result.x) + (result.y * result.y));
	}

private:
	// 원점.
	D3DXVECTOR3 m_ResetPosition;

	// 플레이어 위치.
	D3DXVECTOR3 m_localPosition;

	// 플레이어 바라보는 곳.
	D3DXVECTOR3 m_localLookAt;

	// 플레이어 방향.
	D3DXVECTOR3 m_localDirection;

	// 플레이어 크기.
	D3DXVECTOR3 m_localScale;

	// 위치 행렬.
	D3DXMATRIX m_MatrixPosition;

	// 회전 행렬.
	D3DXMATRIX m_MatrixRotate;

	// 크기 행렬.
	D3DXMATRIX m_MatrixScale;

	// 공전 행렬.
	D3DXMATRIX m_MatrixRevolution;

	// 부모 행렬.
	D3DXMATRIX m_MatrixParent;

	// 월드 행렬.
	D3DXMATRIX m_MatrixWorld;

	// 버텍스.
	D3DXVECTOR3 vertex[4];

	// 기존 버텍스.
	D3DXVECTOR3 vertexOrigin[4];

	// 내 크기.
	float m_fScale;

	float m_rotAngle;

	// 중심 거리차이.
	float m_distance;

	kDIRECTION m_Direction;

	CKDHPlayer* m_Player;
};

