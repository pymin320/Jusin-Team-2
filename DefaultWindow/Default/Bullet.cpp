#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 3.f;
	//m_fAngle2 = 0.f;
	m_fDiagonal = 10.f;

	m_fAngle = 0;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if (m_fAngle != 0)
	{
		m_tInfo.fY += m_fSpeed;
	}
	else
	{
		m_fAngle2 += 20.f;
		m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}*/

	m_tInfo.fY += m_fSpeed;

	/*m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle2 * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle2 * PI) / 180.f)));*/


	//Update_Rect_Missile();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right ||
		100 >= m_tRect.top || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{

}
//void CBullet::Update_Rect_Missile(void)
//{
//	m_Misille.left = LONG(m_tPosin.x - (m_tInfo.fCX * 0.5f));
//	m_Misille.top = LONG(m_tPosin.y - (m_tInfo.fCY * 0.5f));
//	m_Misille.right = LONG(m_tPosin.x + (m_tInfo.fCX * 0.5f));
//	m_Misille.bottom = LONG(m_tPosin.y + (m_tInfo.fCY * 0.5f));
//}
