#pragma once
#include "CObj.h"
#include "CKDHPlayer.h"
#include "Define.h"

class CHexaPad : public CObj
{
public:
	CHexaPad();
	virtual ~CHexaPad();

	// CObj��(��) ���� ��ӵ�
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
	// ����.
	D3DXVECTOR3 m_ResetPosition;

	// �÷��̾� ��ġ.
	D3DXVECTOR3 m_localPosition;

	// �÷��̾� �ٶ󺸴� ��.
	D3DXVECTOR3 m_localLookAt;

	// �÷��̾� ����.
	D3DXVECTOR3 m_localDirection;

	// �÷��̾� ũ��.
	D3DXVECTOR3 m_localScale;

	// ��ġ ���.
	D3DXMATRIX m_MatrixPosition;

	// ȸ�� ���.
	D3DXMATRIX m_MatrixRotate;

	// ũ�� ���.
	D3DXMATRIX m_MatrixScale;

	// ���� ���.
	D3DXMATRIX m_MatrixRevolution;

	// �θ� ���.
	D3DXMATRIX m_MatrixParent;

	// ���� ���.
	D3DXMATRIX m_MatrixWorld;

	// ���ؽ�.
	D3DXVECTOR3 vertex[4];

	// ���� ���ؽ�.
	D3DXVECTOR3 vertexOrigin[4];

	// �� ũ��.
	float m_fScale;

	float m_rotAngle;

	// �߽� �Ÿ�����.
	float m_distance;

	kDIRECTION m_Direction;

	CKDHPlayer* m_Player;
};

