#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

#include <random>


CMonster::CMonster() {}
CMonster::CMonster(MOBTYPE eType)
{
	m_eType = eType;
	m_Side = "����";
	
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

	m_pPlayer = new CPlayer;
  	m_pPattern = new CPattern;
	m_fDiagonal = 30.f;
	
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
	//�߰ݸ��� ���ﰢ�Լ��� ���� ���ϱ�
	/*if (m_eType == MOB_CH)
	{
		//m_fAngle = acos()
	
		float fWidth, fHeight, fDistance;
		

		m_tPlayer.x = m_pPlayer->Get_Info().fX;
		m_tPlayer.y = m_pPlayer->Get_Info().fY;

		//x��ǥ ������ �Ÿ�
		fWidth = fabs(m_tPlayer.x- m_tInfo.fX);

		//y��ǥ ������ �Ÿ�
		fHeight = fabs(m_tPlayer.y - m_tInfo.fY);

		//�밢�� �Ÿ�
		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		//������ǥ�� �÷��̾���ǥ�� ���ΰ�
		m_fAngle = acos(fWidth / fDistance);
		m_Posin.x = m_tInfo.fX;// long(m_tInfo.fX + cosf((m_fAngle * PI) / 180.f));
		m_Posin.y = m_tPlayer.y;//long(m_tInfo.fY - sinf((m_fAngle * PI) / 180.f));

		
		if (m_fAngle > PI / 90);
		{
			m_tInfo.fY -= fDistance * sin(m_fAngle * PI / 180);
			m_tInfo.fX += fDistance * cos(m_fAngle * PI / 180);
		}

		 if (m_fAngle < PI / 90);
		{
			m_tInfo.fY -= fDistance * sin(m_fAngle * PI / 180);
			m_tInfo.fX -= fDistance * cos(m_fAngle * PI / 180);
		}
		
	
			
	}*/

	m_Posin.x = m_tInfo.fX;
	m_Posin.y = m_tInfo.fY + 20.f;
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
	if (m_eType == MOB_CH)
	{	
	
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY,nullptr);
		LineTo(hDC, m_Posin.x, m_Posin.y);
	}

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	//hong modify
	delete m_pPattern;
	m_pPattern = nullptr;
	//end
}

void CMonster::SetBulletList(list<CObj*>* _pBullet)
{
	m_pPattern->Set_BulletList(_pBullet);
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
