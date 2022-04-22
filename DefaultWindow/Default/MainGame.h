#pragma once

#include "Include.h"

#include "Player.h"

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
	/*CObj*	m_pPlayer;
	list<CObj*>	m_BulletList;*/


	list<CObj*>	m_ObjList[OBJ_END];

	TCHAR		m_szFPS[64];	// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
	int			m_iFPS;
	DWORD		m_dwTime;

};

// ������ ���� : �ڵ��� �������� ������ ���·� ����� �����ϱ� ���ϰ� ���� ����

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ�ϴ� ������ �ǹ��Ѵ�.
// ���� ���� �� ���������� ������ �۾��� �߻�ȭ��Ű�� ����� �ǹ��Ѵ�.

// �ݺ���(���ͷ�����)���� : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ������ �ǹ��Ѵ�.
