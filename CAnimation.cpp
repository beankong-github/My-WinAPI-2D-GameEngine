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

		return;
	}

	// =======================
	// �ִϸ��̼� ������ �����ϱ�
	// =======================

	// �ִϸ��̼� �̸�
	fwprintf_s(pFile, L"[Animation_Name]\n");
	fwprintf_s(pFile, m_strName.c_str());
	fwprintf_s(pFile, L"\n\n");

	// ��Ʋ�� �ؽ��� ���� - �̸�, �ּ�
	fwprintf_s(pFile, L"[Atlas_Texture_Name]\n");
	fwprintf_s(pFile, m_pAtlas->GetKey().c_str());
	fwprintf_s(pFile, L"\n\n");

	fwprintf_s(pFile, L"[Atlas_Texture_Address]\n");
	fwprintf_s(pFile, m_pAtlas->GetRelativePath().c_str());
	fwprintf_s(pFile, L"\n\n");

	// �� ������ ����
	fwprintf_s(pFile, L"[Frame_Information]\n");
	fwprintf_s(pFile, L"[Frame_Count]\n");
	fwprintf_s(pFile, L"%d", (int)m_vecFrm.size());
	fwprintf_s(pFile, L"\n\n");

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[Frame_IDX]\n");
		fwprintf_s(pFile, L"%d\n", (int)i);

		fwprintf_s(pFile, L"[Left_Top]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);
		
		fwprintf_s(pFile, L"[Size]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vSize.x, m_vecFrm[i].vSize.y);

		fwprintf_s(pFile, L"[Offset]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		fwprintf_s(pFile, L"[Duration]\n");
		fwprintf_s(pFile, L"%f\n\n", m_vecFrm[i].fDuration);
	}

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

		return;
	}

	// =======================
	// �ִϸ��̼� ������ �о����
	// =======================
	
	// �ִϸ��̼� �̸�
	wchar_t szBuff[256] = L"";
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff,256);
	m_strName = szBuff;

	// ��Ʋ�� �ؽ��� ���� - �̸�, �ּ�
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	wstring strAtlasName = szBuff;

	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	wstring strAtlasRelativePath = szBuff;

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strAtlasName, strAtlasRelativePath);

	// �� ������ ����
	fwscanf_s(pFile, L"%s", szBuff, 256);
	fwscanf_s(pFile, L"%s", szBuff, 256);
	
	int iFrmCount = 0;
	fwscanf_s(pFile, L"%d", &iFrmCount);
	
	for (int i = 0; i < iFrmCount; ++i)
	{
		tAnimFrm frm = {};

		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vLeftTop.x, &frm.vLeftTop.y);

		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vSize.x, &frm.vSize.y);
		
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f %f", &frm.vOffset.x, &frm.vOffset.y);
		
		fwscanf_s(pFile, L"%s", szBuff, 256);
		fwscanf_s(pFile, L"%f", &frm.fDuration);

		m_vecFrm.push_back(frm);
	}

	// ===============
	//	  ���� �ݱ�
	// ===============
	fclose(pFile);

}

