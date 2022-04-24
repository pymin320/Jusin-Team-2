
#pragma once
#include "Obj.h"
#include "CBossFront.h"
#include "AbstractFactory.h"

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
	bool		FrontDead(void) { return false; }
	CObj* Get_BossList() { return m_pBossFront; }
	void	Set_BossList(list<CObj*>* pBoss) { m_pBossList = pBoss; }

	/*void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}*/

private:
	RECT		m_Render;
	POINT		m_tPosin;		//오른쪽 포신
	RECT		m_pRect;

	POINT		m_tPosin2;		//왼쪽 포신
	RECT		m_pRect2;

	DWORD		m_BossTime;
	CObj* m_pBossFront;
	list<CObj*>* m_pBossList;
	int m_Hp;

};