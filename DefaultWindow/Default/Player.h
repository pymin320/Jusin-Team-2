#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Bullet_Default.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Set_BulletList(list<CObj*>* pBullet) { m_pBullet = pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);


private:
	list<CObj*>*			m_pBullet;

	POINT					m_tPosin;
	float					m_fDiagonal;

	// 쉴드 관련
	CObj*					m_pShield;			//쉴드 1
	float					m_fAngle_Shield;
	CObj*					m_pShield2;			//쉴드 2
	float					m_fAngle_Shield2;
	POINT					m_tPosin_Shield;

	// 부가기능
	BOOL					m_bBoost;		// 부스트 모드 여부
	int						m_iHeart;		// 플레이어 목숨


};