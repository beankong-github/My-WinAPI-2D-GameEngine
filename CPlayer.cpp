#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CBullet.h"
#include "CStage.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h  "

CPlayer::CPlayer()
	:m_fSpeed(400.f)
	, m_pTex(nullptr)
{
	//// ���� ���丮 ��� �޾ƿ���
	//wchar_t szPath[256] = {};
	//GetCurrentDirectory(256, szPath);

	//// �����(�÷��̾�) �̹��� ��������
	//wstring strPath = szPath;
	//strPath += L"\\Plane.bmp";

	wstring strContentPath = CPathMgr::GetInst()->GetContentPath();

	// �ؽ�ó �� �� �ε�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerImage", strPath);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	Vec vPos = GetPos();
	
	// Player �̵�
	if (IS_KEY_PRESSED(KEY::LEFT)) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		vPos.x -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::UP))
	{
		vPos.y -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::DOWN))
	{
		vPos.y += m_fSpeed * DS;
	}

	// �Ѿ� ����
	if (IS_KEY_TAP(KEY::SPACE))
	{
		// Bullet �ʱ�ȭ
		CObj* bObj = new CBullet;
		bObj->SetPos(Vec{ GetPos().x, GetPos().y - GetScale().y/2});
		bObj->SetScale(Vec{ 30, 30 });
		
		// StageMgr�κ��� ���� ���������� �����´�
		CStage* curStage = CStageMgr::GetInst()->GetCurStage();
		curStage->AddObject(bObj);
	}
	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	// �̹����� ���
	Vec vPos = GetPos();

	BitBlt(_dc, (int)vPos.x - 32, (int)vPos.y - 32, 64, 64, m_pTex->GetDC(), 0, 0, SRCCOPY);
}
