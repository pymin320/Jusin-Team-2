#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Bullet_Default.h"
#include "CPattern.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	/*void	Set_BulletList(list<CObj*>* pBullet)
	{
		m_pBullet = pBullet;
	}*/
	//void Set_PatternList(CPattern* _pPattern, list<CObj*>* pBullet)
	//{
	//	m_pPattern = _pPattern;
	//	//m_pBullet = pBullet;
	//	m_pPattern->Set_BulletList(pBullet);
	//}
private:
	void		Key_Input(void);

	CObj*		Create_Bullet(DIRECTION eDir);


private:
	typedef list<CObj*>		BULLETLIST;
	BULLETLIST*				m_pBullet;

	POINT					m_tPosin;
	float					m_fDiagonal;

	CObj*					m_pShield2;
	float					m_fAngle2;
	
	CObj*					m_pShield3;
	float					m_fAngle3;

	POINT					m_tPosin_Shield;

};

// 1. 삼각 함수 공부(cos, sin, tan)
// 2. 플레이어 포신 추가하고 회전을 시켜라
// 3. 포신 방향으로 플레이어를 이동해라