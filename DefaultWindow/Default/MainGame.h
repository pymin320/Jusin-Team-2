#pragma once

#include "Include.h"

#include "Player.h"
#include "CPattern.h"
class CMainGame
{
public:				// ������, �Ҹ���
	CMainGame();
	~CMainGame();

// public, protected, private �Լ�
public:
	void	Initialize(void);		// �ʱ�ȭ �Լ�
	void	Update(void);			// �� �����Ӹ��� ���ŵǴ� �����͸� ����� �Լ�
	void	Late_Update(void);
	void	Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void	Release(void);			// �����Ҵ��� �����͸� �����ϴ� �Լ�

// public, protected, private ����
private:
	HDC		m_hDC;
	CObj*	m_pPlayer;
	//list<PATTERN*> m_PatternList;
	CPattern* m_Pattern;

	list<CObj*>	m_ObjList[OBJ_END];

};

