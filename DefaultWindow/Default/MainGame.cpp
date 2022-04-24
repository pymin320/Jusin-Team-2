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



	//공격 몬스터 생성
	/*for (int i = 1; i < 4; ++i)
	{
		m_ObjList[OBJ_FWMONSTER].push_back(CAbstractFactory<CMonster>::Create(float((rand() % 56 + 13) * 10), float((rand() % 30 + 10) * 10), MOB_FW));
		}*/

	

	m_ObjList[OBJ_FWMONSTER].push_back(CAbstractFactory<CMonster>::Create(200, /*float((rand() % 30 + 10) * 10)*/250.f, MOB_FW));
	m_ObjList[OBJ_FWMONSTER].push_back(CAbstractFactory<CMonster>::Create(300, /*float((rand() % 30 + 10) * 10)*/250.f, MOB_FW));
	m_ObjList[OBJ_FWMONSTER].push_back(CAbstractFactory<CMonster>::Create(400, /*float((rand() % 30 + 10) * 10)*/250.f, MOB_FW));

	
	
	//수비 몬스터 생성
	/*for (int i = 0; i < 5; ++i)

	{
		m_ObjList[OBJ_FWMONSTER].push_back(CAbstractFactory<CMonster>::Create(float((rand() % 56 + 13) * 10),75.f,MOB_FW));

	}*/
	m_ObjList[OBJ_DFMONSTER].push_back(CAbstractFactory<CMonster>::Create(125.f, 75.f, MOB_DF));
	m_ObjList[OBJ_DFMONSTER].push_back(CAbstractFactory<CMonster>::Create(225.f, 75.f, MOB_DF));
	m_ObjList[OBJ_DFMONSTER].push_back(CAbstractFactory<CMonster>::Create(325.f, 75.f, MOB_DF));

	m_ObjList[OBJ_DFMONSTER].push_back(CAbstractFactory<CMonster>::Create(475.f, 75.f, MOB_DF));
	m_ObjList[OBJ_DFMONSTER].push_back(CAbstractFactory<CMonster>::Create(575.f, 75.f, MOB_DF));
	m_ObjList[OBJ_DFMONSTER].push_back(CAbstractFactory<CMonster>::Create(675.f, 75.f, MOB_DF));

	//추격 몬스터(ChaseMonster)
	m_ObjList[OBJ_CHMONSTER].push_back(CAbstractFactory<CMonster>::Create(100.f, 100.f, MOB_CH));
	m_ObjList[OBJ_CHMONSTER].push_back(CAbstractFactory<CMonster>::Create(700.f, 100.f, MOB_CH));


		//m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(float(rand() % 56 + 13) * 10, float(rand() % 30 + 13) * 10, 0,"적군"));
 
    //m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(float(rand() % 56 + 13) * 10, float(rand() % 30 + 13) * 10, 0));
		
		//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);
		//((CMonster*)m_ObjList[OBJ_MONSTER].back())->SetPatternBulletList(&m_ObjList[OBJ_BULLET]);
	


	//m_ObjList[OBJ_BOSS].push_back(CAbstractFactory<CBoss>::Create(400, -200, 0, "적군"));
	//dynamic_cast<CBoss*>(m_ObjList[OBJ_BOSS].front())->Set_BulletList(&m_ObjList[OBJ_BULLET]);



#pragma region 복습

	/*if (!m_pPlayer)
	{
		//m_pPlayer = new CPlayer;
		//m_pPlayer->Initialize();
		m_pPlayer = CAbstractFactory<CPlayer>::Create();
	}
	dynamic_cast<CPlayer*>(m_pPlayer)->Set_BulletList(&m_BulletList);*/

#pragma endregion 복습

	


	// UI 그리기 용도
	
	m_pUI = new CUI();
	m_pUI->Set_pPlayer(m_ObjList[OBJ_PLAYER].front());
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
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BOSS], m_ObjList[OBJ_BULLET]);
	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);

}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	//Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}

	m_pUI->Render(m_hDC);
	//m_pUI->Render_PosText(m_hDC, m_ObjList[OBJ_PLAYER].front()->Get_Info().fX, m_ObjList[OBJ_PLAYER].front()->Get_Info().fY, L"Power Up!!!!");
	m_pUI->Render_Score(m_hDC);
	
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
	//hong modify
	//end
	ReleaseDC(g_hWnd, m_hDC);	
	Safe_Delete<CUI*>(m_pUI);
}