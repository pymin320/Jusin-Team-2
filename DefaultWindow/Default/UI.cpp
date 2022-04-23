#include "stdafx.h"
#include "UI.h"
#include "Player.h"


CUI::CUI()
{
	ZeroMemory(m_szMessage, sizeof(TCHAR) * 64);
	ZeroMemory(m_szHeart, sizeof(TCHAR) * 64);

	Initialize();
}


CUI::~CUI()
{
}

void CUI::Initialize(void)
{
	m_iScore = 132340;
}

int CUI::Update(void)
{

	return 0;
}

void CUI::Late_Update(void)
{
}

void CUI::Render(HDC hDC)
{
	Render_Heart(hDC);
}

void CUI::Release(void)
{
}

void CUI::Render_Heart(HDC hDC)
{
	m_iHeart = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Heart();
	switch (m_iHeart)
	{
	case 1:
		lstrcpy(m_szHeart, L"�� ");
		break;
	case 2:
		lstrcpy(m_szHeart, L"�� �� ");
		break;
	case 3:
		lstrcpy(m_szHeart, L"�� �� �� ");
		break;
	case 4:
		lstrcpy(m_szHeart, L"�� �� �� �� ");
		break;
	case 5:
		lstrcpy(m_szHeart, L"�� �� �� �� ��");
		break;
	}
	TextOut(hDC, 20, 20, m_szHeart, lstrlen(m_szHeart));
}

void CUI::Render_Score(HDC hDC)
{

}

void	CUI::Render_PosText(HDC hDC, float _x, float _y, TCHAR _text[64])
{
	lstrcpy(m_szTemp, _text);
	TextOut(hDC, _x, _y, m_szTemp, lstrlen(m_szTemp));
}


// ��Ʈ ��� (���￹��
//
//lstrcpy(m_szFPS, L"Hello");
//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
// 1. dc 2, 3. ����� ������ left, top ��ǥ, 4. ����� ���ڿ� 5. ���ڿ� ���� ũ��
//
//RECT rc{ 0, 0, 50, 50 };
//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
// 1. dc 2. ����� ���ڿ� 3. ���ڿ� ���� ũ�� 4. ����� ��Ʈ �ּ�, 5. ��� �ɼ�
//
//TCHAR	szBuff[32] = L"";
// �Ҽ��� �ڸ� ����� �Ұ����ϴ�. winapi ���̺귯������ �����ϴ� �Լ�
//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
//
// visual c++ ���̺귯������ ����(��� ���� ���ڸ� ����)
//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));