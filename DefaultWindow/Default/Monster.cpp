#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster() {}
CMonster::CMonster(MOBTYPE eType)
{
	m_eType = eType;
}


CMonster::~CMonster()
{
}
void CMonster::Initialize(void)
{	

	if (m_eType == MOB_DF)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 30.f;
		//m_tInfo.fX = float((rand() % 56 + 13) * 10);
		//m_tInfo.fY = float((rand() % 30 + 10) * 10);
		m_fSpeed = 4.f;
	}
	if (m_eType == MOB_FW)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;
		//m_tInfo.fX = float((rand() % 56 + 13) * 10);
		//m_tInfo.fY = 75.f;
		m_fSpeed = 5.f;
	}
}

  
  
int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eType == MOB_DF)
	{
		m_tInfo.fX += m_fSpeed;
	}
	if (m_eType == MOB_FW)
	{
		m_tInfo.fY += m_fSpeed;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (m_eType == MOB_DF)
	{
		if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
			m_fSpeed *= -1.f;
	}
	if (m_eType == MOB_FW)
	{
		
	}
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}
