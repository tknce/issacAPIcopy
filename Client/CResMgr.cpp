#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CResource.h"
#include "CImage.h"
#include "CSound.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	map<wstring, CImage*>::iterator iter = m_mapImage.begin();

	for (; iter != m_mapImage.end(); ++iter)
	{
		delete(iter->second);
	}
	Safe_Del_Map(m_mapSound);
	
}

void CResMgr::init()
{
	
	// 타일
	LoadImg(L"Default", L"image\\isaac\\map\\StoneObject1.bmp");
	LoadImg(L"TutorlalAtlas", L"image\\isaac\\map\\BaseMentTutorial.bmp");
	LoadImg(L"TileAtlas", L"image\\isaac\\Map\\Mapresourse.bmp");
	LoadImg(L"StoneAtlas", L"image\\isaac\\Map\\map.bmp");
	LoadImg(L"BonfireAtlas", L"image\\isaac\\Map\\bonfire.bmp");
	LoadImg(L"EmptyAreaAtlas", L"image\\isaac\\Map\\EmptyArea.bmp");
	LoadImg(L"DoorAtlas", L"image\\isaac\\Map\\Door.bmp");
	LoadImg(L"ShapeAtlas", L"image\\isaac\\Map\\Shape.bmp");

	// 아이템
	LoadImg(L"RedMushroom", L"image\\isaac\\Item\\Mushroom.bmp");

	// Player
	LoadImg(L"PlayerAtlas", L"image\\isaac\\Player\\isaacPlayer.bmp");
	LoadImg(L"TearAtlas", L"image\\isaac\\Tears\\TearsAtlas.bmp");
	LoadImg(L"PlayerTDAtlas", L"image\\isaac\\Tears\\TearsDestoryAtlas.bmp");
	LoadImg(L"MonsterTDAtlas", L"image\\isaac\\Tears\\MonsterTearsDestoryAtlas.bmp");

	// 버튼
	LoadImg(L"ButtonAtlas", L"image\\isaac\\Button\\ButtonAtlas.bmp");




	// Sound
	LoadSound(L"Main", L"Sound\\2\\The_binding_of_Isaac.wav");
	LoadSound(L"Playertear", L"Sound\\3\\bubbles.wav");
	LoadSound(L"PlayerDie", L"Sound\\1\\isaacdies.wav");
	LoadSound(L"Teleport", L"Sound\\2\\hell_portal1.wav");
	LoadSound(L"Roar", L"Sound\\3\\Boss_Lite_SloppyRoar.wav");
	LoadSound(L"Hurt", L"Sound\\1\\Isaac_Hurt_Grunt0.wav");
	LoadSound(L"DoorOpen", L"Sound\\1\\Door_Heavy_Open.wav");
	LoadSound(L"DoorClose", L"Sound\\1\\Door_Heavy_Close.wav");
	LoadSound(L"Boss_Enter", L"Sound\\1\\castleportcullisBossEnter.wav");
	LoadSound(L"Boss_Patten", L"Sound\\2\\Holy.wav");
	LoadSound(L"Light", L"Sound\\1\\Choir_unlock_Item.wav");
	LoadSound(L"Boss_Scared", L"Sound\\2\\Scared_Whimper_1.wav");
	LoadSound(L"Boss_Scared2", L"Sound\\2\\Scared_Whimper_2.wav");
	LoadSound(L"Boss_Tear", L"Sound\\1\\boss2_bubbles0.wav");
	LoadSound(L"Monster_Attack", L"Sound\\3\\Boss_Lite_SloppyRoar.wav");
	LoadSound(L"Monster_Hurt", L"Sound\\1\\goodeath0.wav");
	LoadSound(L"intro", L"Sound\\1\\7689.wav");
	LoadSound(L"GetItem", L"Sound\\1\\Choir_unlock_Item.wav");
	//LoadImg(L"Map", L"image\\Basement_map.bmp");
}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// 해당키로 이미 로딩된게 있으면 해당 리소스를 반환
		return pImage;
	}

	// 해당 키로 로딩된 이미지가 없다.
	
	// content 폴더 경로 + 상대경로 = 최종 경로
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"이미지 로딩 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::CreateImg(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		MessageBox(nullptr, L"중복 키 발생", L"이미지 생성 실패", MB_OK);
		return nullptr;
	}

	// 해당 키로 생성된 이미지가 없다.
	pImage = new CImage;
	if (FAILED(pImage->Create(_iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"이미지 생성 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);	
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
	if (iter != m_mapImage.end())
	{
		return iter->second;
	}

	return nullptr;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (nullptr != pSound)
		return pSound;

	pSound = new CSound;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}
