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


	

	//좌우이동몬스터
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(200,250.f, MOB_FW));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
  
    m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(300, 250.f, MOB_FW));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);
  

	
	//하강몬스터 x,y 좌표 랜더값으로 
	for (int i = 0; i < 15; ++i)
		{
			m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(/*rand() % 600 + 100*/i*50+25, rand() % 900 - 1100, MOB_DF));
			((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);		
	  ((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);	
  }
	

	//추격 몬스터(ChaseMonster)
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(25.f, 25.f, MOB_CH));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);

	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(775.f, 25.f, MOB_CH));
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
	((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetItemList(&m_ObjList[OBJ_ITEM]);

	for (auto& iter : m_ObjList[OBJ_MONSTER])
		iter->Set_Target(m_ObjList[OBJ_PLAYER].front());//몬스터에 있는 setTarget에서 player의 좌표를 받아옴


}

void CMainGame::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
	
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
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

