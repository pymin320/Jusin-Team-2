#include "stdafx.h"
#include "Monster.h"

#include <random>


CMonster::CMonster() {}
CMonster::CMonster(MOBTYPE eType)
{
	m_eType = eType;
}


CMonster::~CMonster()
{
	//hong modify
	Release();
	//end
}
void CMonster::Initialize(void)
{	

	
	
	if (m_eType == MOB_FW)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;
		//m_tInfo.fX = float((rand() % 56 + 13) * 10);
		//m_tInfo.fY = float((rand() % 30 + 10) * 10);
		m_fSpeed = 3.f;
	}
	if (m_eType == MOB_DF)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;
		
		m_fSpeed = 2.f;
	}
	if (m_eType == MOB_CH)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;
		
		m_fSpeed = 2.f;
	}
  	m_pPattern = new CPattern;

}

  
  
int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_eType == MOB_FW)
	{
		m_tInfo.fX += m_fSpeed;
	}
	if (m_eType == MOB_DF)
	{
		m_tInfo.fY += m_fSpeed;
	}
	if (m_eType == MOB_CH)
	{
	
	}


	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{

	if (m_eType == MOB_FW)
	{
		if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
			m_fSpeed *= -1.f;
	}
	if (m_eType == MOB_DF)
	{
		if (WINCY - 400 <= m_tRect.bottom)
			m_fSpeed = 0;
	}
  	m_pPattern->Update(m_Posin, 1);
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	//hong modify
	delete m_pPattern;
	m_pPattern = nullptr;
	//end
}

//void CMonster::SetBulletList(list<CObj*>* _pPattern)
//{
//	//m_pBullet = _pPattern;
//}
//
//void CMonster::SetPatternBulletList(list<CObj*>* pBullet)
//{
//
//	//m_pPattern->Set_BulletList(pBullet);
//}
