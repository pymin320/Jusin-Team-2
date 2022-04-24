#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Bullet_Default.h"
#include "CPattern.h"
#include "UI.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void	Set_BulletList(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	int		Get_Heart() { return m_iHeart; }

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);


private:
	list<CObj*>* m_pBullet;					//메인에서 가져온거
	list <CObj*>	m_ShieldList;
	list<CObj*>* m_pShieldList = &m_ShieldList;

	// 모양 관련
	POINT			PolygonPoint[6];
	POINT			m_tPosin;
	float			m_fDiagonal;

	// 쉴드 관련
	CObj* m_pShield;
	float			m_fAngle_Shield;
	POINT			m_tPosin_Shield;
	float			m_fDiagonal_Shield;

	// 부가기능
	BOOL			m_bBoost;		// 부스트 모드 여부
	int				m_iHeart;		// 플레이어 목숨
	DWORD			m_Time = 0;

	//UI
	CUI*			m_pUI;
//	CPattern*			m_pPattern;

};