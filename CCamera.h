#pragma once
class CCamera
{
	SINGLE(CCamera)

private:
	Vec m_vLookAt;
	Vec m_vDiff;		// �ػ� �߾� ������ ī�޶� �����ִ� ���� ����

public:
	Vec GetDiff() { return m_vDiff; }

public:
	void Init();
	void Update();
};

