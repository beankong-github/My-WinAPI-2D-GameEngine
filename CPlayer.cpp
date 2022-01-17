#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CBullet.h"
#include "CStage.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h  "

CPlayer::CPlayer()
	:m_fSpeed(400.f)
	, m_pTex(nullptr)
{
	// �ؽ�ó �ε�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerImage", L"texture\\Plane.bmp");
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
		CObj* pBullet = new CBullet;

		Vec vPos = GetPos();
		Vec vScale = GetScale();
		pBullet->SetScale(vScale / 2.f);
		vPos = Vec(vPos.x, vPos.y - vScale.y / 2.f);

		CreateObject(pBullet, EOBJ_TYPE::PLAYER_PROJECTILE, vPos);
	}

	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	// �̹����� ���
	Vec vPos = GetPos();

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	//BitBlt(_dc, (int)vPos.x - iWidth/2, (int)vPos.y - iHeight/2, iWidth, iHeight, m_pTex->GetDC(), 0, 0, SRCCOPY);

	TransparentBlt( _dc,
					(int)vPos.x - iWidth / 2,
					(int)vPos.y - iHeight / 2,
					iWidth, iHeight,
					m_pTex->GetDC(),
					0,0,
					iWidth, iHeight,
					RGB(255,0,255));
}  
