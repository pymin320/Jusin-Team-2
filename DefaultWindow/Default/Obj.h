#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }

	void		Set_Dead()				{ m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }


	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

	void		Set_Dead() { m_bDead = true; }
	const string	Get_Side(void) const { return m_Side; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }

protected:
	void		Update_Rect(void);
	

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	string		m_Side;

	float		m_fSpeed;
	float		m_fAngle;

	DIRECTION	m_eDir;
	bool		m_bDead;
	//POINT		m_Posin;
};

