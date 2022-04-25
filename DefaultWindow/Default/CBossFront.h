#pragma once
#include "Obj.h"
#include "CPattern.h"
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
	void Set_BulletList(list<CObj*>* _pBulletList)
	{
		m_pBullet = _pBulletList;
	}
private:
	POINT		m_tPie;			//�߰� �ݿ�
	POINT		m_tPosin;
	DWORD		m_BossTime;
	//RECT		m_PosinRect;
	typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;
	int m_Hp;
	int m_fDiagonal;
	CPattern* m_Pattern;
};

