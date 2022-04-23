#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;

	virtual		void	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
	void Update_Rect_Missile(void);


private :
	POINT m_tPosin;
	float m_fAngle2;
	float m_fDiagonal;
	RECT m_Misille;

};
