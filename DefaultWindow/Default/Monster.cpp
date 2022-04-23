#include "stdafx.h"
#include "Monster.h"
#include <random>

CMonster::CMonster(/*MOBTYPE eMob*/)
{
}


CMonster::~CMonster()
{
	//hong modify
	Release();
	//end
}
void CMonster::Initialize(void)
{	

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 8.f;
	//hong modify
	//rand() % (b+1-a) + a;
	
	m_pPattern = new CPattern;
	//end
}

  
  
int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX += m_fSpeed;
	//hong modify
	m_Posin.x = m_tInfo.fX;
	m_Posin.y = m_tInfo.fY + 30.f;

	
	//end
	Update_Rect();
  
	return OBJ_NOEVENT;

}

void CMonster::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
		m_fSpeed *= -1.f;

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

void CMonster::SetBulletList(list<CObj*>* _pPattern)
{
	m_pBullet = _pPattern;
}

void CMonster::SetPatternBulletList(list<CObj*>* pBullet)
{

	m_pPattern->Set_BulletList(pBullet);
}
