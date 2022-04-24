#pragma once

#include "Obj.h"


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


	static CObj*	Create(float _fX, float _fY, float _fAngle,string _Side)
	{
		CObj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Side(_Side);

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

