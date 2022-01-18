#pragma once

class CObj;

class CComponent
{
private:
	ECOM_TYPE	m_eType;	// ������Ʈ Ÿ�� ��
	CObj*		m_pOwer;	// ������Ʈ�� �����ϰ� �ִ� ��ü ������Ʈ �ּ�

public: 
	ECOM_TYPE GetType() { return m_eType; }
	CObj* GetOwner() { return m_pOwer; }

public:
	virtual void Update() = 0;
	virtual void Render(HDC _dc);

public:
	CComponent(ECOM_TYPE _eType);
	~CComponent();

	friend class CObj;
};

