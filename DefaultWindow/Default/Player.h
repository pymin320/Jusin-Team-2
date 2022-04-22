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

	// ���� ����
	CObj*					m_pShield;			//���� 1
	float					m_fAngle_Shield;
	CObj*					m_pShield2;			//���� 2
	float					m_fAngle_Shield2;
	POINT					m_tPosin_Shield;

	// �ΰ����
	BOOL					m_bBoost;		// �ν�Ʈ ��� ����
	int						m_iHeart;		// �÷��̾� ���


};