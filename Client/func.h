#pragma once

class CObject;
class CCollider;

template<typename T>
bool IsValid(T*& _pPtr)
{
	if (_pPtr->IsDead())
	{
		_pPtr = nullptr;
		return false;
	}

	return true;
}

template<typename T1, typename T2>
void Safe_Del_Map(const map<T1, T2>& _map)
{
	typename map<T1, T2>::const_iterator iter = _map.cbegin();
	for (iter; iter != _map.cend(); ++iter)
	{
		delete iter->second;
	}
}

void SaveWstring(const wstring& _str, FILE* _pFile);
void LoadWstring(wstring& _str, FILE* _pFile);

class CImage;
void SaveImageRef(CImage* _pImage, FILE* _pFile);
void LoadImageRef(CImage** _pImage, FILE* _pFile);


// Angle
// Radian 
// Degree
Vec2 RotateVector(Vec2 _vOrigin, float _Degree);
float CrossVector(Vec2 _v1, Vec2 _v2);

// ==============
// Event Function
// ==============

#include "CEventMgr.h"

template<typename T>
T* Instantiate(Vec2 _vPos, LAYER_TYPE _type)
{
	T* pObject = new T;
	pObject->SetPos(_vPos);

	tEventInfo info = {};
	info.eType = EVENT_TYPE::CREATE_OBJECT;
	info.first = (DWORD_PTR)pObject;
	info.second = (DWORD_PTR)_type;

	CEventMgr::GetInst()->AddEvent(info);

	return pObject;
}


void DeleteObject(CObject* _pObj);
void SceneChange(SCENE_TYPE _eNextScene);


