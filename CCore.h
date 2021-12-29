#pragma once
class CCore
{

private:
	HWND m_hwnd;
	HDC m_hDC;
	POINT m_ptResolution;

public:
	// ������ ���� �̱���
	static CCore* GetInstance()
	{
		static CCore c;			// ���� 1ȸ�� ����ȴ�.
		return &c;
	}

public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void Update();

private:
	CCore();
	~CCore();
};

