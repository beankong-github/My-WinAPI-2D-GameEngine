#include "pch.h"
#include "CBullet.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CMonster.h"

CBullet::CBullet()
	: m_fSpeed(400.f)
	, m_fAddTime(0.f)
	, m_fTailAddTime(0.f)
	, m_pTex(nullptr)
	
{
	// �̸� ����
	SetName(L"Player_Bullet");

	// �浹ü ����
	CCollider* pCol = new CCollider();
	pCol->SetOffsetPos(Vec(0.f, 0.f));
  	pCol->SetScale(Vec(20.f, 20.f));
	AddComponent(pCol);

	// �ؽ�ó �ε�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"EnergyBall", L"texture\\EnergyBall.bmp");


}

CBullet::~CBullet()
{
}

void CBullet::Update()
{
	// �Ѿ� ���� ������Ʈ
	m_fTailAddTime += DS;
	if (m_fTailAddTime > 0.003f)		// 0.02�ʸ��� Tail Update
	{
		m_listTailInfo.push_front(tTailInfo{ GetPos(), CTimeMgr::GetInst()->GetCurTime() });	// ������ ���� ���� ����Ʈ�� �ڷ� �и���
		m_fTailAddTime = 0.f;
	}

	// �ð��� ���� �Ѿ� �Ѿ� ���
	Vec Pos = GetPos();
	Pos.y -= m_fSpeed * DS;
	SetPos(Pos);

	// 2�� �ڸ� �Ѿ� ����
	m_fAddTime += DS;
	if (m_fAddTime >= 4.f)
	{
		DeleteObject(this);
	}
}

void CBullet::Render(HDC _dc)
{
	// ���� �� �귯�� ����
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(66, 198, 255));
	HBRUSH hBrush = CreateSolidBrush(RGB(66, 198, 255));

	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Vec vTailScale = Vec(23.f, 2.f);

	// �Ѿ� ���� ������
	float fCurTime = CTimeMgr::GetInst()->GetCurTime();
	list<tTailInfo>::iterator iter = m_listTailInfo.begin();

	float i = 0.f;

	for (;iter !=  m_listTailInfo.end();)
	{
		if (fCurTime >= iter->fLifeTime + 0.3f)	// ������ 0.3�� �̻� ���� �͵��� ����
		{
			iter = m_listTailInfo.erase(iter);
		}
		else
		{
			Vec vCurScale = vTailScale - i;

			if (vCurScale.x < 0)
			{
				vCurScale.x = 0;
			}

			Vec vTailRenderPos = CCamera::GetInst()->GetRenderPos(iter->vPos);

			// ���� �׸���
			Rectangle(_dc
				, int(vTailRenderPos.x - vCurScale.x / 2.f)
				, int(vTailRenderPos.y - vCurScale.y / 2.f)
				, int(vTailRenderPos.x + vCurScale.x / 2.f)
				, int(vTailRenderPos.y + vCurScale.y / 2.f));

			++iter;
		}
		i += 0.5f;
	}

	// ���� ��, �귯�� ����
	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	// �Ѿ� ������
	Vec vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	TransparentBlt(_dc,
		(int)vRenderPos.x - iWidth / 2,
		(int)vRenderPos.y - iHeight / 2,
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0,
		iWidth, iHeight,
		RGB(255, 0, 255));


#ifdef _DEBUG
	Render_Component(_dc);
#endif
}

void CBullet::OnCollisionEnter(CObj* _pOther)
{
}

void CBullet::OnCollision(CObj* _pOtherObj)
{
	// ���Ϳ� �浹��
	CMonster* pMonster = dynamic_cast<CMonster*>(_pOtherObj);
	if (nullptr != pMonster)
	{
		DeleteObject(this);
	}
}

void CBullet::OnCollisionExit(CObj* _pOther)
{
}

