#pragma once
class CCore
{
private:
	// heap �޸� ���� �̱���
	// static CCore* m_pCore;

public:
	// ������ ���� �̱���
	static CCore* GetInstance()
	{
		static CCore c;			// ���� 1ȸ�� ����ȴ�.
		return &c;
	}
	
	// heap �޸� ���� �̱���
	//static CCore* GetInstance()
	//{
	//	//static CCore c;			// ���� 1ȸ�� ����ȴ�.
	//	//return &c;

	//	if(nullptr == m_pCore)
	//	{
	//		m_pCore = new CCore;
	//	}
	//	return m_pCore;
	//}

	//static void Destroy()
	//{
	//	if (nullptr != m_pCore)
	//	{
	//		delete m_pCore;
	//		m_pCore = nullptr;
	//	}
	//}

private:
	CCore();
	~CCore();
};

