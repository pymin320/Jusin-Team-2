#pragma once
#include "Bullet.h"
class CBulletBomb : public CBullet
{
//���� ���ſ��� y�� +n��ŭ �̵��Ŀ� 360���������� �Ѿ��� �߻�Ǵ�Ŭ����
public:
	CBulletBomb();
	virtual ~CBulletBomb();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};
