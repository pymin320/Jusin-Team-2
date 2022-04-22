#include "stdafx.h"
#include "Bullet_Default.h"


CBulletDefault::CBulletDefault()
{
}


CBulletDefault::~CBulletDefault()
{
	Release();
}

void CBulletDefault::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 5.f;
}

int CBulletDefault::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	/*switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
		
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;

	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	}*/

	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
		
	Update_Rect();

	// Á¶°Ç ? 

	return OBJ_NOEVENT;
}

void CBulletDefault::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right ||
		100 >= m_tRect.top || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true; 
}

void CBulletDefault::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBulletDefault::Release(void)
{
	
}