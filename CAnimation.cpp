#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "CCore.h"

#include "CAnimator.h"
#include "CObj.h"
#include "CTexture.h"

CAnimation::CAnimation()
	: m_strName()
	, m_pAnimator(nullptr)
	, m_pAtlas(nullptr)
	, m_vecFrm(0)
	, m_iCuridx(0)
	, m_fAddTime(0)
	, m_bFinish(0)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bFinish)
		true;

	m_fAddTime += DS;

	if (m_fAddTime >= m_vecFrm[m_iCuridx].fDuration)
	{
		++m_iCuridx;
		if (m_iCuridx >= m_vecFrm.size())
		{
			m_iCuridx -= 1;		// ������ ������
			m_bFinish = true;
			return;
		}
		 m_fAddTime = m_fAddTime - m_vecFrm[m_iCuridx].fDuration;
	}
}

void CAnimation::Render(HDC _dc)
{
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetOwner()->GetPos());

	TransparentBlt(_dc
		, int(vRenderPos.x - m_vecFrm[m_iCuridx].vSize.x / 2.f + m_vecFrm[m_iCuridx].vOffset.x)	// x
		, int(vRenderPos.y - m_vecFrm[m_iCuridx].vSize.y / 2.f + m_vecFrm[m_iCuridx].vOffset.y)	// y
		, int(m_vecFrm[m_iCuridx].vSize.x)	// width
		, int(m_vecFrm[m_iCuridx].vSize.y)	// height
		, m_pAtlas->GetDC()	// Src's HDC
		, int(m_vecFrm[m_iCuridx].vLeftTop.x)	// x pos in atlas
		, int(m_vecFrm[m_iCuridx].vLeftTop.y)	// y pos in atlas
		, int(m_vecFrm[m_iCuridx].vSize.x)		// width in atlas
		, int(m_vecFrm[m_iCuridx].vSize.y)		// height int atlas
		, RGB(255, 0, 255));
}

void CAnimation::Create(const wstring& _strAnimName, CTexture* _pAtlasTex, Vec _vLeftTop, Vec _vSize, Vec _vOffset, float _fxDistance, float _fDuration, UINT _iFrmCount)
{
	m_strName = _strAnimName;
	m_pAtlas = _pAtlasTex;
	
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrmCount; i++)
	{
		frm.vLeftTop = Vec(_vLeftTop.x + (float)i * _fxDistance, _vLeftTop.y);
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.fDuration = _fDuration;
	
		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Reset()
{
	m_iCuridx = 0;
	m_fAddTime = 0.f;
	m_bFinish = false;
}

CObj* CAnimation::GetOwner()
{ 
	return m_pAnimator->GetOwner();
}

void CAnimation::Save(const wstring& _strRelativeFolderPath)
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativeFolderPath;
	strFilePath += m_strName;
	strFilePath += L".anim";
	
	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// ���� ������ ������ �ּҰ��� �޾ư��� ������ �ּҸ� �������ش�.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"�ִϸ��̼� ���� ����", MB_OK);
	}

	// =======================
	// �ִϸ��̼� ������ �����ϱ�
	// =======================

	// �ִϸ��̼� �̸�
	SaveWString(m_strName, pFile);
	
	// ��Ʋ�� �ؽ��� ���� - �̸�, �ּ�
	SaveWString(m_pAtlas->GetKey(), pFile);
	SaveWString(m_pAtlas->GetRelativePath(), pFile);

	// �� ������ ����
	size_t iFrmCount = m_vecFrm.size();
	fwrite(&iFrmCount, sizeof(size_t), 1, pFile);
	fwrite(m_vecFrm.data(), sizeof(tAnimFrm), m_vecFrm.size(), pFile);

	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativeFilePath)
{
	// ===============
	//	���� ��� ã��
	// ===============
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;
	

	// ===============
	//	  ���� ����
	// ===============
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// �ش� ����� ������ �б� ���� ���� ���� ������ ������ �ּҰ��� ������ �ּҸ� �������ش�.

	if (nullptr == pFile)
	{
		wchar_t szErr[256] = {};
		errno_t err = GetLastError();
		wsprintf(szErr, L"���� �߻�, �����ڵ�: %d", err);
		MessageBox(CCore::GetInst()->GetMainWndHWND(), szErr, L"�ִϸ��̼� �ε� ����", MB_OK);
	}


	// =======================
	// �ִϸ��̼� ������ �о����
	// =======================
	
	// �ִϸ��̼� �̸�
	LoadWString(m_strName, pFile);		
	
	// ��Ʋ�� �ؽ��� ���� - �̸�, �ּ�
	wstring strAtlasName;
	wstring strAtlasRelativePath;

	LoadWString(strAtlasName, pFile);
	LoadWString(strAtlasRelativePath, pFile);

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strAtlasName, strAtlasRelativePath);

	// �� ������ ����
	size_t iFrmCount = 0;
	fread(&iFrmCount, sizeof(size_t), 1, pFile);
	
	for (size_t i = 0; i < iFrmCount; ++i)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}


	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);

}

