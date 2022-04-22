#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_iHeart = 5;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 10.f;
	m_fDiagonal = 100.f;

	m_fAngle_Shield = 0.f;
	m_fAngle_Shield2 = 180.f;
	m_bBoost = true;

	if (m_bBoost)
	{
		m_pShield = new CShield();
		m_pShield2 = new CShield();
	}

}

int CPlayer::Update(void)
{
	if (m_bDead)
	{
		if (m_iHeart)
			--m_iHeart;
		else
			return OBJ_END;
	}

	// ������ ����
	Key_Input();
	m_fAngle_Shield += 3.f;
	m_fAngle_Shield2 += 3.f;


	// ��� ������ ���� �ڿ� �������� ��ǥ�� �ϼ�
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle * PI) / 180.f)));

	// ���� 1
	m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle_Shield * PI) / 180.f)));
	m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle_Shield * PI) / 180.f)));
	m_pShield->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
	m_pShield->Late_Update();

	// ���� 2
	m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle_Shield2 * PI) / 180.f)));
	m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle_Shield2 * PI) / 180.f)));
	m_pShield2->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
	m_pShield2->Late_Update();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);

	m_pShield->Render(hDC);
	m_pShield2->Render(hDC);
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	// �Ѿ� �߻�
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));

		// ����2 �Ѿ� �߻�
		POINT temp = { dynamic_cast<CShield*>(m_pShield)->Get_PosinPoint().x,
			dynamic_cast<CShield*>(m_pShield)->Get_PosinPoint().y };
		m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)temp.x, (float)temp.y, m_fAngle));

		// ����3 �Ѿ� �߻�
		temp = { dynamic_cast<CShield*>(m_pShield2)->Get_PosinPoint().x,
			dynamic_cast<CShield*>(m_pShield2)->Get_PosinPoint().y };
		m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)temp.x, (float)temp.y, m_fAngle));
	}

	// ���� ȸ��
	if (GetAsyncKeyState('A'))
		m_fAngle += 5.f;

	if (GetAsyncKeyState('D'))
		m_fAngle -= 5.f;

	// �÷��̾� �̵�
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_tInfo.fX > 0)					// ȭ�� ��Ż ����
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (m_tInfo.fY < 600)		// ȭ�� ��Ż ����
				{
					m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
					m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (m_tInfo.fY > 0)			// ȭ�� ��Ż ����
				{
					m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
					m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
				}
			}
			else
				m_tInfo.fX -= m_fSpeed;
		}

	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_tInfo.fX < 800)				// ȭ�� ��Ż ����
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (m_tInfo.fY < 600)		// ȭ�� ��Ż ����
				{
					m_tInfo.fX += m_fSpeed / sqrtf(2.f);
					m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (m_tInfo.fY > 0)			// ȭ�� ��Ż ����
				{
					m_tInfo.fX += m_fSpeed / sqrtf(2.f);
					m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
				}
			}
			else
				m_tInfo.fX += m_fSpeed;
		}
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		if (m_tInfo.fY > 0)		// ȭ�� ��Ż ����
		{
			m_tInfo.fY -= m_fSpeed;
		}
	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_tInfo.fY < 600)	// ȭ�� ��Ż ����
		{
			m_tInfo.fY += m_fSpeed;
		}
	}
}
