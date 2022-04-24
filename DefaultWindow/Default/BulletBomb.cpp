#include "stdafx.h"
#include "BulletBomb.h"

CBulletBomb::CBulletBomb()
{
}

CBulletBomb::~CBulletBomb()
{
    Release();
}

void CBulletBomb::Initialize(void)
{
}

int CBulletBomb::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBulletBomb::Late_Update(void)
{
}

void CBulletBomb::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBulletBomb::Release(void)
{
}
