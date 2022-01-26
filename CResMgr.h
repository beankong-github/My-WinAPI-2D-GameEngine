#pragma once

// �ѹ� ������� ���ҽ��� �ߺ��Ǿ� ��������� �ʵ��� ����

class CTexture;

class CResMgr
{
	SINGLE(CResMgr);

private:
	map<wstring, CTexture*> m_mapTex;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreateTexture(const wstring& _strKey, UINT _iWidthm, UINT _iHeight);
	CTexture* FindTexture(const wstring& _strKey);

};

