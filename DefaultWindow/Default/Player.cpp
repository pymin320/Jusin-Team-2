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
	m_fDiagonal = 70.f;

	m_fAngle_Shield = 90.f;
	m_bBoost = true;


	if (m_bBoost)	// 부스트 모드이면, 쉴드 2개 생성
	{
		for (int i = 0; i < 2; ++i)
		{
			m_pShieldList->push_back(CAbstractFactory<CShield>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle_Shield));
		}
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

	// 키입력시 연산
	Key_Input();

	// 쉴드 좌표 움직이게
	m_fAngle_Shield += 3.f;

	// 최종좌표 전달
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle * PI) / 180.f)));

	for (auto& _shield : *m_pShieldList)
	{
		m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle_Shield * PI) / 180.f)));
		m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle_Shield * PI) / 180.f)));

		_shield->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
		_shield->Late_Update();

		m_fAngle_Shield += 180.f;
	}
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);

	for (auto& _shield : *m_pShieldList)
	{
		_shield->Render(hDC);
	}
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{

	// 총알 발사
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (m_bBoost)
		{
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
		}
		else
		{
			m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
		}


		for (auto& _shield : *m_pShieldList)
		{
			POINT temp = { dynamic_cast<CShield*>(_shield)->Get_PosinPoint().x,
				dynamic_cast<CShield*>(_shield)->Get_PosinPoint().y };
			m_pBullet->push_back(CAbstractFactory<CBulletDefault>::Create((float)temp.x, (float)temp.y, m_fAngle));
		}
	}

	// 포신 회전
	if (GetAsyncKeyState('A'))
		m_fAngle += 5.f;

	if (GetAsyncKeyState('D'))
		m_fAngle -= 5.f;

	// 플레이어 이동
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_tInfo.fX > 0)					// 화면 이탈 방지
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (m_tInfo.fY < 600)		// 화면 이탈 방지
				{
					m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
					m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (m_tInfo.fY > 0)			// 화면 이탈 방지
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
		if (m_tInfo.fX < 800)				// 화면 이탈 방지
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (m_tInfo.fY < 600)		// 화면 이탈 방지
				{
					m_tInfo.fX += m_fSpeed / sqrtf(2.f);
					m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (m_tInfo.fY > 0)			// 화면 이탈 방지
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
		if (m_tInfo.fY > 0)		// 화면 이탈 방지
		{
			m_tInfo.fY -= m_fSpeed;
		}
	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_tInfo.fY < 600)	// 화면 이탈 방지
		{
			m_tInfo.fY += m_fSpeed;
		}
	}
}
