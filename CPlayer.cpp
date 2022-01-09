#include "pch.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CBullet.h"
#include "CCore.h"
#include "CStage.h"

CPlayer::CPlayer()
	:m_fSpeed(400.f)	
{
}

CPlayer::~CPlayer()
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
		bObj->SetPos(GetPos());
		bObj->SetScale(Vec{ 30, 30 });
		g_stage.AddObject(bObj);
	}
	SetPos(vPos);
}

void CPlayer::Render(HDC _dc)
{
	CObj::Render(_dc);
}
