#include "pch.h"
#include "CCollider.h"
#include "CObj.h"

// �浹 �˸�
void CCollider::OnCollision(CCollider* _pCollider)
{
	GetOwner()->OnCollision(_pCollider->GetOwner());
}

CCollider::CCollider()
	: CComponent(ECOM_TYPE::COLLIDER)
	, m_vOffsetPos{}
	, m_vScale{}
	, m_vFinalPos{}
{
}

CCollider::~CCollider()
{
}

void CCollider::Update()
{
	// �浹ü�� �̹� �������� ���� ��ġ
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::Render(HDC _dc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(120, 250, 50));
	HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	HPEN hPrevPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBrush);

	Rectangle(_dc
		, int(m_vFinalPos.x - m_vScale.x / 2.f)
		, int(m_vFinalPos.y - m_vScale.y / 2.f)
		, int(m_vFinalPos.x + m_vScale.x / 2.f)
		, int(m_vFinalPos.y + m_vScale.y / 2.f));

	SelectObject(_dc, hPrevPen);
	SelectObject(_dc, hPrevBrush);

	DeleteObject(hPen);
}
