#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_liFreqency;
	LARGE_INTEGER m_liPrevCount;
	LARGE_INTEGER m_liCurCount;

	float m_fDS;			// delta secound : 1 �����ӿ� �ɸ� �ð�
	float m_fAddTime;		// 1�� ã��
	float m_fCurTime;		// ��� �ð� (�ʴ���) 

	UINT m_iFPS;			// frame per second

public:
	void Init();
	void Update();

public:
	float GetDS()		{ return m_fDS;}
	float GetCurTime()	{ return m_fCurTime; }
	UINT GetFPS()		{ return m_iFPS;}

};

