#pragma once
class CCore
{

private:
	HWND m_hwnd;

public:
	// ������ ���� �̱���
	static CCore* GetInstance()
	{
		static CCore c;			// ���� 1ȸ�� ����ȴ�.
		return &c;
	}

	int Init(HWND _hwnd, POINT _ptResolution);

private:
	CCore();
	~CCore();
};

