#include "stdafx.h"
#include "CPattern.h"
#include "AbstractFactory.h"
#include <random>
CPattern::CPattern()
{
	Initialize();
} 

CPattern::~CPattern()
{
}

void CPattern::Initialize()
{
	m_DelayTime = rand() % (4000 + 1 - 1000) + 1000;
}

void CPattern::Attack(POINT& _Posin)
{

	m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)_Posin.x, (float)_Posin.y));
	m_pBullet->back()->Side("Àû±º");
	
}

void CPattern::Set_BulletList(list<CObj*>* pBullet)
{
	
	m_pBullet = pBullet;
	
}

void CPattern::Update(POINT& _Posin, int i)
{
	switch (i)
	{
	case 1:
	{
		DWORD currentTickCount = GetTickCount();
		if (currentTickCount - m_Time >= m_DelayTime)
		{
			m_Time = GetTickCount();
			Attack(_Posin);
		}
	}
		break;
	}

}
