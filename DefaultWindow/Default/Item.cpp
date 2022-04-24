#include "stdafx.h"
#include "Item.h"

CItem::CItem()
{
	Initialize();
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	//임시
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 100.f;
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 2.f;
	m_ySpeed = 2.f;
	m_Side = "적군";

	m_pUI = new CUI();
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	m_tInfo.fY += m_fSpeed;

	Update_Rect();
}

void CItem::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(250, 225, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	m_pUI->Render_UI_PosText(hDC, m_tInfo.fX - 5, m_tInfo.fY - 7, L"S");
}

void CItem::Release(void)
{
}



