#include "pch.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CObject.h"
#include "CTile.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CResMgr.h"
#include "CKeyMgr.h"



CScene::CScene()
	: m_iTileCol(0)
	, m_iTileRow(0)
	, m_iTileMapCol(0)
	, m_iTileMapRow(0)
	, m_bColliderMode(false)
	, m_bTileMode(false)
	, m_bScene(false)
	, m_iMiniMapIdx(0)
	, m_bDoorSound(true)
{
	

}

CScene::~CScene()
{
	DeleteAllObject();
}


void CScene::CreateTile(UINT _iCol, UINT _iRow)
{
	DeleteObject(LAYER_TYPE::TILE);

	m_iTileCol = _iCol;
	m_iTileRow = _iRow;



	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(iCol * WALLW_SIZE ), (float)(iRow * WALLH_SIZE)));
			
			AddObject(pTile, LAYER_TYPE::TILE);
		}
	}
}

void CScene::CreateTile1(UINT _iCol, UINT _iRow, OBJECT_TYPE _objtype)
{
	
	DeleteObject(LAYER_TYPE::MAP);

	
	m_iTileMapCol = _iCol;
	m_iTileMapRow = _iRow;

	CreateTile2(15 * _iCol, 9 * _iRow, OBJECT_TYPE::DEFAULT, LAYER_TYPE::TILE);
}

void CScene::CreateTile2(UINT _iCol, UINT _iRow, OBJECT_TYPE _obj_type, LAYER_TYPE _layer_type)
{
	
	DeleteObject(LAYER_TYPE::TILE);

	m_iTileCol = _iCol;
	m_iTileRow = _iRow;
	int Col = 0;
	int Row = 0;
	


	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		int Row1 = iRow / 9;
		if (Row1 >= 1)
		{
			Row = 96 * Row1;
		}

		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			int Col1 = iCol / 15;
			if (Col1 >= 1 )
			{
				Col = 126 * Col1;
			}

			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(iCol * WALLW_SIZE + Col) , (float)(iRow * WALLH_SIZE + Row)));
			
			pTile->SetType(_obj_type);
			AddObject(pTile, _layer_type);
		}
		Col = 0;
	}
}

void CScene::MiniMap()
{
	const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);

	const vector<CObject*>& m_Player = GetObjects(LAYER_TYPE::PLAYER);
	Vec2 PlayerPos = ((CPlayer*)m_Player[0])->GetPos();
	int iMaxCol = ((CPlayer*)m_Player[0])->GetPos().x / 1280;
	int iMaxRow = ((CPlayer*)m_Player[0])->GetPos().y / 717;
	int iCol = iMaxCol * 15;
	int iRow = iMaxRow * 9;

	int iIdx = iRow * GetTileCol() + iCol;


	if (m_iMiniMapIdx != iIdx && ((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::MAP)
	{
		((CTile*)vecObj[m_iMiniMapIdx])->SetMiniMaptypeEntered();
	}

	if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::MAP)
	{
		((CTile*)vecObj[iIdx])->SetMiniMaptypeEnter();
		m_iMiniMapIdx = iIdx;
	}
}

void CScene::Door()
{
	const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);

	const vector<CObject*>& m_Player = GetObjects(LAYER_TYPE::PLAYER);
	Vec2 PlayerPos = ((CPlayer*)m_Player[0])->GetPos();
	int iMaxCol = ((CPlayer*)m_Player[0])->GetPos().x / 1280;
	int iMaxRow = ((CPlayer*)m_Player[0])->GetPos().y / 720;
	iMaxCol += 1;
	iMaxRow += 1;
	const vector<CObject*>& m_Monster = GetObjects(LAYER_TYPE::MONSTER);
	for (size_t i = 0; i < m_Monster.size(); i++)
	{


		Vec2 MonsterPos = m_Monster[i]->GetPos();

		if (iMaxCol * 1280 < MonsterPos.x || iMaxRow * 720 < MonsterPos.y)
		{
			continue;
		}
		if (iMaxCol * 1280 > MonsterPos.x && (iMaxCol - 1) * 1280 < MonsterPos.x
			&& iMaxRow * 720 > MonsterPos.y && (iMaxRow - 1) * 720 < MonsterPos.y)
		{
			iMaxCol -= 1;
			iMaxRow -= 1;

			int iCol = iMaxCol * 15;
			int iRow = iMaxRow * 9;
			if (m_bDoorSound)
			{
				CSound* pBgm = CResMgr::GetInst()->FindSound(L"DoorClose");
				if (nullptr != pBgm)
					pBgm->Play(false);
				m_bDoorSound = false;
			}
			int iIdx = iRow * GetTileCol() + iCol + 7;
			if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
			{
				((CTile*)vecObj[iIdx])->SetImgIdx(4);
			}
			iIdx = iRow * GetTileCol() + iCol + (4 * GetTileCol());
			if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
			{
				((CTile*)vecObj[iIdx])->SetImgIdx(6);
			}
			iIdx = iRow * GetTileCol() + iCol + (4 * GetTileCol()) + 14;
			if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
			{
				((CTile*)vecObj[iIdx])->SetImgIdx(5);
			}
			iIdx = iRow * GetTileCol() + iCol + (8 * GetTileCol()) + 7;
			if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
			{
				((CTile*)vecObj[iIdx])->SetImgIdx(7);
			}
			return;
		}	
		
	}
	if (!m_bDoorSound)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"DoorOpen");
		if (nullptr != pBgm)
			pBgm->Play(false);
		m_bDoorSound = true;
	}


	iMaxCol -= 1;
	iMaxRow -= 1;

	int iCol = iMaxCol * 15;
	int iRow = iMaxRow * 9;

	int iIdx = iRow * GetTileCol() + iCol + 7;
	if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
	{
		((CTile*)vecObj[iIdx])->SetImgIdx(0);
	}
	iIdx = iRow * GetTileCol() + iCol + (4 * GetTileCol());
	if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
	{
		((CTile*)vecObj[iIdx])->SetImgIdx(2);
	}
	iIdx = iRow * GetTileCol() + iCol + (4 * GetTileCol()) + 14;
	if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
	{
		((CTile*)vecObj[iIdx])->SetImgIdx(1);
	}
	iIdx = iRow * GetTileCol() + iCol + (8 * GetTileCol()) + 7;
	if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
	{
		((CTile*)vecObj[iIdx])->SetImgIdx(3);
	}

	return;
}





void CScene::SceneMove()
{
	if (IsTap(KEY_TYPE::J))
	{
		GetSwich();
		if (!GetSwich())
			SetSwich(true);
		else
			SetSwich(false);
	}
	if (IsTap(KEY_TYPE::K))
	{
		GetTileSwich();
		if (!GetTileSwich())
			SetTileSwich(true);
		else
			SetTileSwich(false);
	}

	if (IsTap(KEY_TYPE::N_1))
	{
		SceneChange(SCENE_TYPE::TOOL);
	}
	if (IsTap(KEY_TYPE::N_2))
	{
		SceneChange(SCENE_TYPE::LOGO);
	}
	if (IsTap(KEY_TYPE::N_3))
	{
		SceneChange(SCENE_TYPE::START);
	}
	if (IsTap(KEY_TYPE::N_4))
	{
		SceneChange(SCENE_TYPE::STAGE_01);
	}
	if (IsTap(KEY_TYPE::N_5))
	{
		SceneChange(SCENE_TYPE::ENDING);
	}
}

void CScene::SetFocusedUI(CObject* _pUI)
{
	// Focused 처리 하려는 UI 를 UI 레이어 벡터 안에서 찾아서 지우고
	vector<CObject*>::iterator iter = m_arrLayer[(UINT)LAYER_TYPE::UI].begin();
	for (; iter != m_arrLayer[(UINT)LAYER_TYPE::UI].end(); ++iter)
	{
		if (*iter == _pUI)
		{
			m_arrLayer[(UINT)LAYER_TYPE::UI].erase(iter);
			break;
		}
	}

	// 다시 맨 뒤로 넣는다.
	m_arrLayer[(UINT)LAYER_TYPE::UI].push_back(_pUI);
}




void CScene::tick()
{	
	

	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->tick();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if (i == (UINT)LAYER_TYPE::TILE)
			render_tile(_dc);
		else
		{
			vector<CObject*>::iterator iter = m_arrLayer[i].begin();
			for (; iter != m_arrLayer[i].end();)
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}	
	}
}

void CScene::DeleteAllObject()
{
	for (size_t i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObject((LAYER_TYPE)i);
	}

}

void CScene::DeleteObject(LAYER_TYPE _eType)
{

	vector<CObject*>& vecObj = m_arrLayer[(UINT)_eType];

	
		for (UINT j = 0; j < vecObj.size(); ++j)
		{
			SAFE_DELETE(vecObj[j]);
		}

		vecObj.clear();
	
}

void CScene::render_tile(HDC _dc)
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCamLT = CCamera::GetInst()->GetLookAt() - (vResolution / 2.f);

	// tool 해상도 조절
	
	if (m_bScene)
	{
		vResolution.x = vResolution.x + 360.f - (WALLW_SIZE *2);
		vResolution.y = vResolution.y + 180.f;
	}
	

	// 화면 안에 들어오는 최대 타일 개수
	int iMaxCol = (int)(vResolution.x / (float)WALLW_SIZE) + 1;
	int iMaxRow = (int)(vResolution.y / (float)WALLH_SIZE) + 1;

	// 카메라 좌상단 위치가 몇행 몇 열인지 계산
	int iLTCol = (int)(vCamLT.x / (float)WALLW_SIZE);
	int iLTRow = (int)(vCamLT.y / (float)WALLH_SIZE);

	// MAP 별 Tile 보이는 위치 보정
	int Col = 0;
	int Row = 0;
	Col = iLTCol / 15;
	Row = iLTRow / 9;
	if (iLTCol >= 15)
	{
		iLTCol = (int)((vCamLT.x -(126 * Col)) / (float)WALLW_SIZE);
	}
	if(iLTRow >= 9)
	{
		iLTRow = (int)((vCamLT.y + (0 * Row)) / (float)WALLW_SIZE);
	}
	
	

	vector<CObject*>& vecTile = m_arrLayer[(UINT)LAYER_TYPE::TILE];

	for (int j = 0; j < iMaxRow; ++j)
	{
		for (int i = 0; i < iMaxCol; ++i)
		{
			int iRow = iLTRow + j;
			int iCol = iLTCol + i;

			



			if (iRow < 0|| (int)GetTileRow()<= iRow
				|| iCol < 0 || (int)GetTileCol() <= iCol)
			{
				continue;
			}

			int iTileIdx = iRow * GetTileCol() + iCol;
			vecTile[iTileIdx]->render(_dc);
		}
	}
}

