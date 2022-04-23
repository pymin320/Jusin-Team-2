#include "stdafx.h"
#include "CPattern.h"
#include "AbstractFactory.h"
CPattern::CPattern()
{
	Initialize();
} 

CPattern::~CPattern()
{
}

void CPattern::Initialize()
{
}

void CPattern::Attack(POINT& _Posin)
{
	//m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)_Posin.x, (float)_Posin.y, DIR_UP));
}
