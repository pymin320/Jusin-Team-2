#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"

CPlayer::CPlayer()
{
	Initialize();
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 10.f;
	m_fDiagonal = 100.f;

	m_fAngle2 = 0.f;
	m_fAngle3 = 180.f;


	m_pShield2 = new CShield();
	m_pShield3 = new CShield();

}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	// 연산을 진행
	Key_Input();
	m_fAngle2 += 3.f;
	m_fAngle3 += 3.f;
	

	// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle * PI) / 180.f)));
	


	m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle2 * PI) / 180.f)));
	m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle2 * PI) / 180.f)));
	m_pShield2->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
	m_pShield2->Late_Update();

	m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle3 * PI) / 180.f)));
	m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle3 * PI) / 180.f)));
	m_pShield3->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
	m_pShield3->Late_Update();

}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);

	m_pShield2->Render(hDC);
	m_pShield3->Render(hDC);

}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	// GetKeyState
	/*if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))

		m_tInfo.fY += m_fSpeed;*/

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
		
		// 쉴드2 총알 발사
		POINT temp = { dynamic_cast<CShield*>(m_pShield2)->Get_PosinPoint().x,
					   dynamic_cast<CShield*>(m_pShield2)->Get_PosinPoint().y };
		m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)temp.x, (float)temp.y, m_fAngle));

		// 쉴드3 총알 발사
		temp = { dynamic_cast<CShield*>(m_pShield3)->Get_PosinPoint().x,
				 dynamic_cast<CShield*>(m_pShield3)->Get_PosinPoint().y };
		m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)temp.x, (float)temp.y, m_fAngle));
	}
		

	if (GetAsyncKeyState('A'))
		m_fAngle += 5.f;

	/*if (GetAsyncKeyState('S'))
		m_pBullet->push_back(Create_Bullet(DIR_DOWN));*/

	if (GetAsyncKeyState('D'))
		m_fAngle -= 5.f;


	/*if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else
			m_tInfo.fX -= m_fSpeed;
	}
	
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}

		else
			m_tInfo.fX += m_fSpeed;
	}
		
	else if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;*/


	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX += m_fSpeed * cosf(((m_fAngle + 90.f) * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(((m_fAngle + 90.f) * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX -= m_fSpeed * cosf(((m_fAngle + 90.f) * PI) / 180.f);
		m_tInfo.fY += m_fSpeed * sinf(((m_fAngle + 90.f) * PI) / 180.f);
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}
		
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX -= m_fSpeed * cosf((m_fAngle * PI) / 180.f);
		m_tInfo.fY += m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	}

}

CObj* CPlayer::Create_Bullet(DIRECTION eDir)
{
	CObj*		pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, eDir);
	return pBullet;
}
