#pragma once
#include "CObj.h"

class CPlayer
	: public CObj
{
private:
	float m_fSpeed;		// �ʴ�  �̵� �ȼ�

public:
	void SetSpeed(float _speed){ m_fSpeed = _speed; }
	float GetSpeed() { return m_fSpeed;}

public:
	void Update() override;
	void Render(HDC _dc);

public:
	CPlayer();
	~CPlayer();
};

