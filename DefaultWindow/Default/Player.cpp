#include "stdafx.h"
#include "Player.h"
#include "CPattern.h"

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
	m_tPosin.x = (long)m_tInfo.fX;
	m_tPosin.y = (long)m_tInfo.fY;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	// ������ ����
	Key_Input();



	// ��� ������ ���� �ڿ� �������� ��ǥ�� �ϼ�
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	// GetKeyState
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
	
	
	
	//1�ʿ� �ѹ����
	DWORD currentTickCount = GetTickCount();
	if (currentTickCount - m_Time >= 1000)
	{
		m_pPattern->Attack(m_tPosin);
		m_Time = GetTickCount();
	}
}
