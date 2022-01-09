#pragma once

class CStage;

class CStageMgr
{
	SINGLE(CStageMgr);

private:
	CStage* m_arrStage[(UINT)ESTAGE_TYPE::STAGE_END];	// ��� �������� �迭
	CStage* m_pCurStage; // ���� ��������

public:
	CStage* GetCurStage() { return m_pCurStage; }

public:
	void Init();
	void Update();
	void Render(HDC _dc);
};

