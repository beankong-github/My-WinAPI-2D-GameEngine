#pragma once

// vs, debug, release � ������� �����ϵ� ������ ��η� ������ ���ҽ� ������ �� �ְ� ��
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_strContentPath[255];

public:
	void Init();

public:
	const wchar_t* GetContentPath() { return  m_strContentPath; }
};

