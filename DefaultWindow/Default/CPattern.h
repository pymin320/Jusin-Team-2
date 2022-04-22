#pragma once
#include "Bullet.h"
class CPattern
{
public:
	CPattern();
	~CPattern();
public:
	void Initialize();
	void Attack(POINT& _Posin);
public:
	void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}

private:
	DWORD m_Time;
	list<CObj*>* m_pBullet;
	float		m_fAngle;
};

