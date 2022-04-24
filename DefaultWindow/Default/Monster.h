#pragma once
#include "Obj.h"
//hong modify
#include "CPattern.h" 
//end
class CMonster :public CObj
{
public:

	CMonster();
	CMonster(MOBTYPE eType );
	virtual~CMonster();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void SetBulletList(list<CObj*>* _pBullet);
private:
	MOBTYPE		m_eType;
	CPattern* m_pPattern;	
	POINT m_Posin;
	float m_TempAngle;
};

