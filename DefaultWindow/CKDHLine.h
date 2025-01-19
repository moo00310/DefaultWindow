#pragma once
#include "CObj.h"
#include "CKDHPlayer.h"

class CKDHLine : public CObj
{
public:
	CKDHLine();
	virtual ~CKDHLine();

	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	void SetRotateAngle(float _angle);

private:
	// 원점.
	D3DXVECTOR3 m_ResetPosition;

	// 내 위치.
	D3DXVECTOR3 m_localPosition;

	// 부모 위치.
	D3DXVECTOR3 m_localParentPosition;

	// 내 크기.
	D3DXVECTOR3 m_localScale;

	// 자식 위치 행렬.
	D3DXMATRIX m_MatrixPosition;

	// 자식 회전 행렬.
	D3DXMATRIX m_MatrixRotate;

	// 자식 크기 행렬.
	D3DXMATRIX m_MatrixScale;

	// 자식 공전 행렬.
	D3DXMATRIX m_MatrixRevolution;

	// 자식 부모 행렬.
	D3DXMATRIX m_MatrixParent;

	// 자식 월드 행렬.
	D3DXMATRIX m_MatrixWorld;

	// 버텍스.
	D3DXVECTOR3 vertex[2];

	// 기존 버텍스.
	D3DXVECTOR3 vertexOrigin[2];

	// 내 크기.
	float m_fScale;

	// 공전 각도.
	float m_revolAngle;

	float m_revOriginAngle;

	// 자전 각도.
	float m_rotAngle;

	CKDHPlayer* m_Player;
};

