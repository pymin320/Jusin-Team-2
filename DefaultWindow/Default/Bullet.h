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
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void SetDamege(float _fDamage) { m_fDamage = _fDamage; }
private:
	float m_fDamage;
	POINT					m_tPosin;

};

