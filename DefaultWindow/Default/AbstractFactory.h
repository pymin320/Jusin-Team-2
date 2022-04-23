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
};

