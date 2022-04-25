#pragma once
#include "Obj.h"
#include "Bullet.h"


class CBoss :
    public CObj
{
public:
	CBoss();
	virtual ~CBoss();

	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);

	void	Set_BulletList(list<CObj*>* pBullet) { m_pBullet = pBullet; }

private:
	POINT		m_tPosin;		//오른쪽 포신
	RECT		m_pRect;
	POINT		m_tPosin2;		//왼쪽 포신
	RECT		m_pRect2;

	POINT		m_tPie;			//중간 반원
	RECT		m_pRect3;

	DWORD		m_BossTime;

	typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;
};

