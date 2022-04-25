#pragma once

#include "Obj.h"
#include "CPattern.h"

template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create(string _Side)
	{
		CObj*	pObj = new T;
		pObj->Initialize();
		pObj->Side(_Side);
		return pObj;
	}

	//���� �Ķ���� ������ 
	static CObj* Create(float _fX, float _fY, MOBTYPE eType)
	{
		CObj* pObj = new T(eType);
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		return pObj;
	}


	static CObj*	Create(float _fX, float _fY, float _fAngle)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create(float _fX, float _fY, float _fAngle, CPattern* m_Pattern)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		dynamic_cast<CMonster*>(pObj)->SetPattern(m_Pattern);
		return pObj;
	}
	static CObj* Create(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if (DIR_END >= eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}
};

