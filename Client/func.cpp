#include "pch.h"
#include "func.h"

#include "CObject.h"
#include "CImage.h"
#include "CResMgr.h"

void DeleteObject(CObject* _pObj)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::DELETE_OBJECT;
	info.first = (DWORD_PTR)_pObj;
	CEventMgr::GetInst()->AddEvent(info);
}

void SceneChange(SCENE_TYPE _eNextScene)
{
	tEventInfo info = {};
	info.eType = EVENT_TYPE::SCENE_CHANGE;
	info.first = (DWORD_PTR)_eNextScene;
	CEventMgr::GetInst()->AddEvent(info);

}

void SaveWstring(const wstring& _str, FILE* _pFile)
{
	size_t iLen = _str.length();
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(_str.c_str(), sizeof(wchar_t), iLen, _pFile);
}

void LoadWstring(wstring& _str, FILE* _pFile)
{
	size_t iLen = _str.length();
	wchar_t szBuff[256] = {};

	fread(&iLen, sizeof(size_t), 1, _pFile);
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}

void SaveImageRef(CImage* _pImage, FILE* _pFile)
{
	int iCheck = 1;
	if (nullptr == _pImage)
	{
		iCheck = 0;
		fwrite(&iCheck, sizeof(int), 1, _pFile);
	}
	else
	{
		fwrite(&iCheck, sizeof(int), 1, _pFile);

		const wstring& strKey = _pImage->GetKey();
		const wstring& strPath = _pImage->GetRelativePath();

		SaveWstring(strKey, _pFile);
		SaveWstring(strPath, _pFile);
	}
}

void LoadImageRef(CImage** _pImage, FILE* _pFile)
{
	int iCheck = 0;
	fread(&iCheck, sizeof(int), 1, _pFile);

	if (0 == iCheck)
		return;

	wstring strKey;
	wstring strRelativePath;

	LoadWstring(strKey, _pFile);
	LoadWstring(strRelativePath, _pFile);

	*_pImage = CResMgr::GetInst()->LoadImg(strKey, strRelativePath);
}

Vec2 RotateVector(Vec2 _vOrigin, float _Degree)
{
	float fRadian = (_Degree / 180.f) * PI;

	_vOrigin.Normalize();

	return Vec2(cosf(fRadian) * _vOrigin.x - sinf(fRadian) * _vOrigin.y
		, sinf(fRadian) * _vOrigin.x + cosf(fRadian) * _vOrigin.y);
}

float CrossVector(Vec2 _v1, Vec2 _v2)
{
	return _v1.x * _v2.y - _v1.y * _v2.x;
}