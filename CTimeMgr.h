#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_liFreqency;
	LARGE_INTEGER m_liPrevCount;
	LARGE_INTEGER m_liCurCount;

	float m_fDS;			// delta secound : 1 �����ӿ� �ɸ� �ð�
	float m_fOneSec;		// 1�� ã��
	UINT m_iFPS;			// frame per second
	UINT m_iElapsedTime;	// ��� �ð� (�ʴ���) 

public:
	void Init();
	void Update();

public:
	float GetDS() { return m_fDS; }
	UINT GetFPS() { return m_iFPS; }
};

