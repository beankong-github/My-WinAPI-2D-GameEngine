#pragma once

// vs, debug, release � ������� �����ϵ� ������ ��η� ������ ���ҽ� ������ �� �ְ� ��
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	void Init();
public:
	wchar_t* GetContentPath();
};

