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

// 1. �ﰢ �Լ� ����(cos, sin, tan)
// 2. �÷��̾� ���� �߰��ϰ� ȸ���� ���Ѷ�
// 3. ���� �������� �÷��̾ �̵��ض�