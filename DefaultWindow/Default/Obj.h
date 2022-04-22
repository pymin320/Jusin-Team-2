#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual		void	Initialize(void)	PURE;
	virtual		void	Update(void)		PURE;
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
	bool		m_bDead;
};

