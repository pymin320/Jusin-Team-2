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
	int		Get_Heart() { return m_iHeart; }
	int		Get_BoostCount() { return m_iBoostCount; }

	void	Set_BulletList(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void	Set_ItemShield() { m_bShield = true; }
	void	Set_ItemSpeed() { m_fSpeed *= 1.3f; }
	void	Set_HDC(HDC hDC) { m_hDC = hDC; }

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input();


private:
	HDC				m_hDC;
	list<CObj*>*	m_pBullet;					//메인에서 가져온거
	list <CObj*>	m_ShieldList;
	list<CObj*>*	m_pShieldList = &m_ShieldList;

	// 모양 관련
	POINT			PolygonPoint[6];
	POINT			m_tPosin;
	float			m_fDiagonal;

	// 쉴드 관련
	CObj*			m_pShield;
	float			m_fAngle_Shield;
	POINT			m_tPosin_Shield;
	float			m_fDiagonal_Shield;

	// 부가기능
	BOOL			m_bBoost;		// 부스트 모드 여부
	BOOL			m_bShield;		// 쉴드 모드 여부
	int				m_iHeart;		// 플레이어 목숨
	int				m_iBoostCount;
	/*int				m_iBoostFail;*/
	int				m_iGageScore;
	DWORD			m_Time;
	DWORD			m_Time2;
	DWORD			m_Time3;

//	CPattern*			m_pPattern;

};