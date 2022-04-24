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
	void	Set_BulletList(list<CObj*>* pBullet);
	void Update(POINT& _Posin, int i = 1);

	

private:
	list<CObj*>* m_pBullet;
	DWORD m_Time = GetTickCount();
	DWORD m_DelayTime;
	float		m_fAngle;
};

