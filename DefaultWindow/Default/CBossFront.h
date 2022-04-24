#pragma once
#include "Obj.h"
class CBossFront :
    public CObj
{
	CBossFront();
	virtual ~CBossFront();

	virtual		void	Initialize(void);
	virtual		int		Update(void);
	virtual		void	Late_Update(void);
	virtual		void	Render(HDC hDC);
	virtual		void	Release(void);
};

