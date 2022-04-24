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
	m_iBoostCount = 2;
	m_iGageScore = 1;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	PolygonPoint[0] = { (long)m_tInfo.fX, (long)m_tInfo.fY - 50 };
	PolygonPoint[1] = { (long)m_tInfo.fX + 50, (long)m_tInfo.fY };
	PolygonPoint[2] = { (long)m_tInfo.fX + 50, (long)m_tInfo.fY + 50 };
	PolygonPoint[3] = { (long)m_tInfo.fX, (long)m_tInfo.fY };
	PolygonPoint[4] = { (long)m_tInfo.fX - 50 , (long)m_tInfo.fY + 50 };
	PolygonPoint[5] = { (long)m_tInfo.fX - 50, (long)m_tInfo.fY };

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;
	m_fDiagonal = 50.f;

	m_fAngle_Shield = 90.f;
	m_bBoost = false;
	m_bShield = false;
	m_fDiagonal_Shield = 80.f;
	
	m_Side = "아군";

	m_Time = GetTickCount();		// 쉴드 타이머
	m_Time2 = GetTickCount();       // 총알 타이머
	m_Time3 = GetTickCount();		// 부스트 타이머

	//m_pPattern = new CPattern;
	//m_pPattern->Set_BulletList(m_pBullet);

	//쉴드부터 생성
	for (int i = 0; i < 2; ++i)
	{
		m_pShieldList->push_back(CAbstractFactory<CShield>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle_Shield));
	}
}

int CPlayer::Update(void)
{
	if (m_bDead)
	{
		if (m_iHeart)
		{
			--m_iHeart;
			m_bDead = false;

			if (m_iHeart <= 0)
			{
				return OBJ_DEAD;
			}
		}
		else
			return OBJ_DEAD;
	}

	if (g_iScore >= m_iGageScore * 50)
	{
		++m_iBoostCount;
		++m_iGageScore;
	}

	// 키입력시 연산
	Key_Input();
	PolygonPoint[0] = { (long)m_tInfo.fX, (long)m_tInfo.fY - 30 };
	PolygonPoint[1] = { (long)m_tInfo.fX + 30, (long)m_tInfo.fY};
	PolygonPoint[2] = { (long)m_tInfo.fX + 30, (long)m_tInfo.fY + 30};
	PolygonPoint[3] = { (long)m_tInfo.fX, (long)m_tInfo.fY};
	PolygonPoint[4] = { (long)m_tInfo.fX - 30 , (long)m_tInfo.fY + 30 };
	PolygonPoint[5] = { (long)m_tInfo.fX - 30, (long)m_tInfo.fY};

	// 쉴드 좌표 움직이게
	m_fAngle_Shield += 3.f;

	// 쉴드 타이머
	if (m_bShield)
	{
		DWORD CurrentTime = GetTickCount();
		if (CurrentTime - m_Time > 5000)
		{
			m_bShield = false;
			m_Time = GetTickCount();
		}
	}

	// 부스트 타이머
	if (m_bBoost)
	{
		DWORD CurrentTime = GetTickCount();
		if (CurrentTime - m_Time3 > 5000)
		{
			m_bBoost = false;
			m_Time3 = GetTickCount();
		}
	}

	// 최종좌표 전달
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle * PI) / 180.f)));

	if (m_bShield)
	{
		for (auto& _shield : *m_pShieldList)
		{
			m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal_Shield * cosf((m_fAngle_Shield * PI) / 180.f)));
			m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal_Shield * sinf((m_fAngle_Shield * PI) / 180.f)));

			_shield->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
			_shield->Late_Update();

			m_fAngle_Shield += 180.f;
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Polygon(hDC, PolygonPoint, 6);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);


	if(m_bShield)
	{
		for (auto& _shield : *m_pShieldList)
		{
			_shield->Render(hDC);
		}
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 15, L"Shield!!!");
	}


	if (m_bBoost)
	{
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 15, L"Boost!!!");
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 30, L"Speed Up!!!");
	}
}

void CPlayer::Release(void)
{
	//Safe_Delete<CPattern*>(m_pPattern);
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_CONTROL))
	{
		if (GetTickCount() - m_Time2 > 150)
		{
			if (m_iBoostCount > 0)
			{
				m_bBoost = true;
				--m_iBoostCount;
			}
			m_Time2 = GetTickCount();
		}
	}

	// 총알 발사
	if (GetAsyncKeyState(VK_SPACE))
	{		
		if (GetTickCount() - m_Time2 > 150)
		{
			if (m_bShield)
			{
				m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
				m_pBullet->back()->Side("아군");
				m_pBullet->back()->Set_Speed(-3.f);

				for (auto& _shield : *m_pShieldList)
				{
					POINT temp = { dynamic_cast<CShield*>(_shield)->Get_PosinPoint().x,
									dynamic_cast<CShield*>(_shield)->Get_PosinPoint().y };
					m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)temp.x, (float)temp.y, m_fAngle));
					m_pBullet->back()->Side("아군");
					m_pBullet->back()->Set_Speed(-3.f);
				}
			}
			else if (!m_bBoost)
			{
				m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
				m_pBullet->back()->Side("아군");
				m_pBullet->back()->Set_Speed(-3.f);
			}
			m_Time2 = GetTickCount();
		}

		if (GetTickCount() - m_Time2 > 120)
		{
			if (m_bBoost)
			{
				//총알 3발
				m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x - 10, (float)m_tPosin.y, m_fAngle));
				m_pBullet->back()->Side("아군");
				m_pBullet->back()->Set_Speed(-3.f);

				m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
				m_pBullet->back()->Side("아군");
				m_pBullet->back()->Set_Speed(-3.f);

				m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x + 10, (float)m_tPosin.y, m_fAngle));
				m_pBullet->back()->Side("아군");
				m_pBullet->back()->Set_Speed(-3.f);
			}
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
			{
				m_tInfo.fX -= m_fSpeed;
			}
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
