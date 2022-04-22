#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster(/*MOBTYPE eMob*/)
{

}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{	

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 8.f;
}

int CMonster::Update(void)
{
	m_tInfo.fX += m_fSpeed;
	Update_Rect();
	return 0;
}

void CMonster::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{

}

