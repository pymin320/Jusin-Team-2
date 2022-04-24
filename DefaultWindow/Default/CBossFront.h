#pragma once
#include "Obj.h"
class CBossFront :
	public CObj
{
public:
	CBossFront();
	virtual ~CBossFront();

	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
	bool		Dead();



private:
	POINT		m_tPie;			//중간 반원

	DWORD		m_BossTime;
	/*typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;*/
	int m_Hp;
};

