#pragma once
#include "Obj.h"

class CUI
{
public:
	CUI();
	~CUI();

	void	Initialize(void);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
	void	Set_Data(float _data) { m_fData = _data; }
	void	Set_pPlayer(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

	void	Render_Heart(HDC hDC);
	void	Render_Score(HDC hDC);
	void	Render_PosText(HDC hDC, float _x, float _y, TCHAR _text[64]);



private:
	CObj* m_pPlayer;

	float		m_fData;
	TCHAR		m_szMessage[64];

	// 플레이어 목숨 표시
	int			m_iHeart;
	TCHAR		m_szHeart[64];

	//Render_PosText에서 사용되는 Temp문자열
	TCHAR		m_szTemp[64];

	// 스코어 전역변수 필요
	int			m_iScore;
};

