#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"

int		g_iScore = 0;

CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create("아군"));
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletList(&m_ObjList[OBJ_BULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_ItemList(&m_ObjList[OBJ_ITEM]);


	
	////공격 몬스터 생성
	//m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(200,250.f, MOB_FW));
	//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]); // 얘네 다 서진 추가

	//
 //   m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(300, 250.f, MOB_FW));
	//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);

	//m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(400, 250.f, MOB_FW));
	//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);

	//dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_HDC(m_hDC);
	


	////수비 몬스터 생성
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(125.f, 75.f, MOB_DF));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->Set_Angle(-90.f);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(225.f, 75.f, MOB_DF));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->Set_Angle(-90.f);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(325.f, 75.f, MOB_DF));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->Set_Angle(-90.f);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(475.f, 75.f, MOB_DF));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->Set_Angle(-90.f);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(575.f, 75.f, MOB_DF));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->Set_Angle(-90.f);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(675.f, 75.f, MOB_DF));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->Set_Angle(-90.f);

	////추격 몬스터(ChaseMonster)
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(100.f, 100.f, MOB_CH));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(700.f, 100.f, MOB_CH));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);

	//m_ObjList[OBJ_BOSS].push_back(CAbstractFactory<CBoss>::Create(400, -200, 0, "적군"));
	//dynamic_cast<CBoss*>(m_ObjList[OBJ_BOSS].front())->Set_BulletList(&m_ObjList[OBJ_BULLET]);
}

void CMainGame::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);

				if (m_ObjList[OBJ_PLAYER].size() == 0)
				{
					// 게임오버 처리 추가 필요
					PostQuitMessage(0);
				}
			}
			else
				++iter;
		}
	}
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_BULLET]);
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}

	CUI::Render_UI(m_hDC, m_ObjList[OBJ_PLAYER].front());
	CUI::Render_UI_Score(m_hDC);
	
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
	ReleaseDC(g_hWnd, m_hDC);	
}

