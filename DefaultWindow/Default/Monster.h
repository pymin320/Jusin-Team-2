#pragma once
#include "Obj.h"
//hong modify
#include "CPattern.h" 
//end
class CMonster :public CObj
{
public:
	CMonster(/*MOBTYPE eMob*/ );
	virtual~CMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
//hong modify
public:
	void SetBulletList(list<CObj*>* pBullet);
	void SetPatternBulletList(list<CObj*>* pBullet);
private:
	typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;

	CPattern* m_pPattern;
	POINT m_Posin;
	
//end
};

