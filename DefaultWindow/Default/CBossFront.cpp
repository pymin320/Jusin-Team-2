

#include "stdafx.h"
#include "CBossfront.h"

CBossFront::CBossFront()
	:m_BossTime(GetTickCount())
{
}

CBossFront::~CBossFront()
{
}

void CBossFront::Initialize(void)
{
	m_tInfo.fX = 400;
	m_tInfo.fY = -200;
	m_fAngle = 0;

	m_tInfo.fCX = 900;
	m_tInfo.fCY = 200;
	m_Hp = 10;

	m_ySpeed = 1.0f;
	m_fSpeed = 0.2f;
	m_Side = "Àû±º";
}

int CBossFront::Update(void)
{
	if (m_bDead)
	{
		m_Hp = 0;
		/*if (m_Hp <= 0)
		{
			return OBJ_DEAD;
		}*/
	}


	m_tInfo.fX += m_fSpeed;
	if (m_BossTime + 3000 <= GetTickCount())
	{
		m_tInfo.fY += m_ySpeed;
	}

	Update_Rect();


	m_tRect.right = m_tInfo.fX + 100;
	m_tRect.left = m_tInfo.fX - 100;
	m_tRect.top = m_tInfo.fY + 100;
	m_tRect.bottom = m_tInfo.fY + 130;

	return OBJ_NOEVENT;
}



void CBossFront::Late_Update(void)
{
	if (275 >= m_tRect.left || 535 <= m_tRect.right)
		m_fSpeed *= -1.f;
	if (110 < m_tRect.bottom)
		m_ySpeed = 0;
}

void CBossFront::Render(HDC hDC)
{
	if (m_Hp > 0)
	{
		Pie(hDC, m_tRect.left, m_tRect.top - 60, m_tRect.right, m_tRect.bottom + 20, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom - 30);
	}
}

void CBossFront::Release(void)
{
}

bool CBossFront::Dead()
{
	if (m_Hp <= 0)
	{
		return true;
	}
	else
		return false;
}