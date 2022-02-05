#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CStage.h"
#include "CTexture.h"
#include "CBullet.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: m_fSpeed(300.f)
	, m_pTex(nullptr)
{
	// �̸� ����
	SetName(L"Player");

	// �ؽ�ó �ε�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerImage", L"texture\\Plane.bmp");

	// �浹ü ����
	CCollider* pCol = new CCollider;
	pCol->SetOffsetPos(Vec(0.f, 0.f));
	pCol->SetScale(Vec(60.f, 40.f));
	AddComponent(pCol);

	// �ִϸ��̼� ����
	CTexture* pAnimAtlasTex = CResMgr::GetInst()->LoadTexture(L"PlayerAnimation", L"texture\\animation\\link_0.bmp");
	CAnimator* pAnimator = new CAnimator;
	
	//pAnimator->CreateAnimation(L"IDLE", pAnimAtlasTex, Vec(0.f, 0.f), Vec(60.f, 65.f), Vec(0.f,0.f), 60.f, 0.1f, 3);
	//pAnimator->CreateAnimation(L"WALK_DOWN", pAnimAtlasTex, Vec(0.f, 260.f), Vec(60.f, 65.f), Vec(0.f, 0.f), 60.f, 0.05f, 10);
	//pAnimator->CreateAnimation(L"WALK_UP", pAnimAtlasTex, Vec(0.f, 390.f), Vec(60.f, 65.f), Vec(0.f, 0.f), 60.f, 0.05f, 10);
	//pAnimator->CreateAnimation(L"WALK_RIGHT", pAnimAtlasTex, Vec(0.f, 325.f), Vec(60.f, 65.f), Vec(0.f, 0.f), 60.f, 0.05f, 10);
	//pAnimator->CreateAnimation(L"WALK_LEFT", pAnimAtlasTex, Vec(0.f, 455.f), Vec(60.f, 65.f), Vec(0.f,0.f),60.f, 0.05f, 10);
	//

	//CAnimation* pSaveAnim = nullptr;
	//pSaveAnim = pAnimator->FindAnimation(L"IDLE");
	//pSaveAnim->Save(L"animation\\player\\");

	//pSaveAnim = pAnimator->FindAnimation(L"WALK_DOWN");
	//pSaveAnim->Save(L"animation\\player\\");

	//pSaveAnim = pAnimator->FindAnimation(L"WALK_UP");
	//pSaveAnim->Save(L"animation\\player\\");

	//pSaveAnim = pAnimator->FindAnimation(L"WALK_RIGHT");
	//pSaveAnim->Save(L"animation\\player\\");	
	//
	//pSaveAnim = pAnimator->FindAnimation(L"WALK_LEFT");
	//pSaveAnim->Save(L"animation\\player\\");

	/*CAnimation* pLoadAnim = new CAnimation;
	pLoadAnim->Load(L"animation\\player\\IDLE.anim");*/

	pAnimator->LoadAnimation(L"animation\\player\\IDLE.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALK_UP.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALK_RIGHT.anim");
	pAnimator->LoadAnimation(L"animation\\player\\WALK_LEFT.anim");
 
	AddComponent(pAnimator);
	pAnimator->PlayAnimation(L"IDLE");
	
}


CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	Vec vPos = GetPos();
	
	// Player �̵�
	if (IS_KEY_PRESSED(KEY::A)) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		vPos.x -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::D))
	{
		vPos.x += m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::W))
	{
		vPos.y -= m_fSpeed * DS;
	}
	if (IS_KEY_PRESSED(KEY::S))
	{
		vPos.y += m_fSpeed * DS;
	}
	
	if (IS_KEY_TAP(KEY::A)) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		GetAnimator()->PlayAnimation(L"WALK_RIGHT");
	}
	if (IS_KEY_TAP(KEY::D))
	{
		GetAnimator()->PlayAnimation(L"WALK_LEFT");
	}
	if (IS_KEY_TAP(KEY::W))
	{
		GetAnimator()->PlayAnimation(L"WALK_UP");
	}
	if (IS_KEY_TAP(KEY::S))
	{
		GetAnimator()->PlayAnimation(L"WALK_DOWN");
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
	//Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());	// ī�޶� ��ġ�� ���� �÷��̾� ���� ������ ��ġ ���ϱ�

	//UINT iWidth = m_pTex->Width();
	//UINT iHeight = m_pTex->Height();

	////BitBlt(_dc, (int)vPos.x - iWidth/2, (int)vPos.y - iHeight/2, iWidth, iHeight, m_pTex->GetDC(), 0, 0, SRCCOPY);

	//TransparentBlt( _dc,
	//				(int)vRenderPos.x - iWidth / 2,
	//				(int)vRenderPos.y - iHeight / 2,
	//				iWidth, iHeight,
	//				m_pTex->GetDC(),
	//				0,0,
	//				iWidth, iHeight,
	//				RGB(255,0,255));

 	Render_Component(_dc);
}

void CPlayer::OnCollisionEnter(CObj* _pOther)
{
}

void CPlayer::OnCollision(CObj* _pOther)
{
}

void CPlayer::OnCollisionExit(CObj* _pOther)
{
}
