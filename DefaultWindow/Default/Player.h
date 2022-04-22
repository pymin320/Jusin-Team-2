#pragma once
#include "Obj.h"
#include "CPattern.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	/*void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}*/
	void Set_PatternList(CPattern* _pPattern, list<CObj*>* pBullet)
	{
		m_pPattern = _pPattern;
		//m_pBullet = pBullet;
		m_pPattern->Set_BulletList(pBullet);
	}
private:
	void		Key_Input(void);
	CPattern* m_pPattern;
	typedef list<CObj*>		BULLETLIST;
	BULLETLIST* m_pBullet;
	POINT					m_tPosin;

	DWORD m_Time = GetTickCount();//юс╫ц©К
};

