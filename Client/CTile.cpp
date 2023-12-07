#include "pch.h"
#include "CTile.h"


#include "CScene.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "CImage.h"

#include "CKeyMgr.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CIsaacTear.h"
#include "CDeadIsaac.h"
#include "CMiniMap.h"


CTile::CTile()
	: m_pTileAtlas(nullptr)
	, m_iImgidx(0)
	, m_Objecttype(OBJECT_TYPE::DEFAULT)
	, m_pMiniMap(nullptr)
	, m_bForbiden(true)
{
	m_pTileAtlas = CResMgr::GetInst()->LoadImg(L"Default", L"image\\isaac\\Map\\StoneObject1.bmp");
	
	if(m_Objecttype == OBJECT_TYPE::MAP)
	{
		return;
	}

	if (m_Objecttype == OBJECT_TYPE::DEFAULT)
	{
		return;
	}
	/*AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(WALLW_SIZE, WALLH_SIZE));*/
	

}

CTile::~CTile()
{
}
void CTile::SetColliderScale(Vec2 _scale)
{
	m_VColliderScale = _scale; 
	if (GetCollider() != nullptr)
		GetCollider()->SetScale(m_VColliderScale);

}
void CTile::SetColliderOffset(Vec2 _offset)
{
	m_VColliderOffset = _offset; 
	if (GetCollider() != nullptr)
		GetCollider()->SetOffset(m_VColliderOffset);
}
void CTile::SetMiniMap()
{
	Vec2 a = GetPos();

	int iMaxCol = this->GetPos().x / 1280;
	int iMaxRow = this->GetPos().y / 717;


	m_pMiniMap = Instantiate<CMiniMap>(Vec2(1280.f -  154.f + (float)(26 * iMaxCol), 48.f + (float)(18 * iMaxRow)), LAYER_TYPE::ETCUI);
	m_pMiniMap->SetMiniMaptype(3);
	
}
void CTile::SetMiniMaptypeEnter()
{
	if(nullptr!= m_pMiniMap)
	 m_pMiniMap->SetMiniMapEnter(); 
}
void CTile::SetMiniMaptypeEntered()
{
	if (nullptr != m_pMiniMap)
	m_pMiniMap->SetMiniMapEntered();
}
void CTile::AddImgIdx()
{
	++m_iImgidx;

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	if (iMaxCol * iMaxRow <= m_iImgidx)
	{
		m_iImgidx = 0;
	}

}

void CTile::Typerender(HDC _dc)
{
	if (nullptr == m_pTileAtlas || m_iImgidx == -1)
		return;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	int iRow = m_iImgidx / iMaxCol;
	int iCol = m_iImgidx % iMaxCol;

	vRenderPos.x += 63;
	vRenderPos.y += 48;


	/*AlphaBlend(_dc, (int)vRenderPos.x, (int)vRenderPos.y
		, WALLW_SIZE, WALLH_SIZE
		, m_pTileAtlas->GetDC(), WALLW_SIZE * iCol, WALLH_SIZE * iRow
		, WALLW_SIZE, WALLH_SIZE, tFunc1);*/

	TransparentBlt(_dc
		, (int)vRenderPos.x, (int)vRenderPos.y
		, WALLW_SIZE, WALLH_SIZE
		, m_pTileAtlas->GetDC()
		, TILE_SIZE * iCol, TILE_SIZE * iRow
		, TILE_SIZE, TILE_SIZE
		, RGB(255, 0, 255));
}

void CTile::AddForbidden(CCollider* _pCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	float fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y);
	float fScale = (pPlayer->GetCollider()->GetScale().y / 2.f + (GetCollider()->GetScale().y / 2.f));

	Vec2 PlayerPos = pPlayer->GetCollider()->GetFinalPos();
	


	// 타일의 y값을 구하기
	float if1 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2));
	float if2 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) + GetCollider()->GetScale().y;

	float Playerposup = PlayerPos.y - pPlayer->GetCollider()->GetScale().y / 2 + pPlayer->GetCollider()->GetScale().y-3;
	float Playerposdown = PlayerPos.y + pPlayer->GetCollider()->GetScale().y / 2 - pPlayer->GetCollider()->GetScale().y+3;

	if (m_bForbiden)
	{
		// 타일의 y와 플레이어의 y을 비교해 안에 들어가 있으면 y값 코드 진행
		if (Playerposup >= (if1) && Playerposdown <= (if2))
		{
			fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x);
			fScale = (pPlayer->GetCollider()->GetScale().x / 2.f + (GetCollider()->GetScale().x / 2.f));

			// y축에서 접근한다면 왼쪽인지 오른쪽인지 판단
			if ((pPlayer->GetCollider()->GetFinalPos().x < GetCollider()->GetFinalPos().x))
			{
				if (Playerposup < Playerposdown + pPlayer->GetCollider()->GetFinalPos().y / 2)
				{
					if (fLen < fScale)
					{
						Vec2 vPlayerPos = pPlayer->GetPos();
						vPlayerPos.x -= (fScale - fLen) + 1.f;

						pPlayer->SetPos(vPlayerPos);
						return;
					}
				}

				if (Playerposup > Playerposdown)
				{
					if (fLen < fScale)
					{
						Vec2 vPlayerPos = pPlayer->GetPos();
						vPlayerPos.x -= (fScale - fLen) + 1.f;

						pPlayer->SetPos(vPlayerPos);
						return;
					}
				}


			}
			else
			{

				if (fLen < fScale)
				{
					Vec2 vPlayerPos = pPlayer->GetPos();
					vPlayerPos.x += (fScale - fLen) + 1.f;
					pPlayer->SetPos(vPlayerPos);
					return;
				}
			}
		}
	}

	// x축에서 접근한다면 위쪽인지 아닌지 판단
	if ((pPlayer->GetCollider()->GetFinalPos().y < GetCollider()->GetFinalPos().y))
	{
		m_bForbiden = false;
		if (fLen < fScale)
		{
			Vec2 vPlayerPos = pPlayer->GetPos();
			vPlayerPos.y -= (fScale - fLen) + 1.f;
			pPlayer->SetPos(vPlayerPos);
			return;
		}
	}
	else
	{
		m_bForbiden = false;
		if (fLen < fScale)
		{
			Vec2 vPlayerPos = pPlayer->GetPos();
			vPlayerPos.y += (fScale - fLen) + 1.f;
			pPlayer->SetPos(vPlayerPos);
			return;
		}
		
	}

}
void CTile::AddForbidden1(CCollider* _pCollider)
{
	CMonster* pPlayer = dynamic_cast<CMonster*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	float fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y);
	float fScale = (pPlayer->GetCollider()->GetScale().y / 2.f + (GetCollider()->GetScale().y / 2.f));

	Vec2 PlayerPos = pPlayer->GetCollider()->GetFinalPos();


	// 타일의 y값을 구하기
	float if1 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2));
	float if2 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) + GetCollider()->GetScale().y;

	// 타일의 y와 플레이어의 y을 비교해 안에 들어가 있으면 y값 코드 진행
	if (PlayerPos.y >= (if1) && PlayerPos.y <= (if2))
	{
		fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x);
		fScale = (pPlayer->GetCollider()->GetScale().x / 2.f + (GetCollider()->GetScale().x / 2.f));

		// y축에서 접근한다면 왼쪽인지 오른쪽인지 판단
		if ((pPlayer->GetCollider()->GetFinalPos().x < GetCollider()->GetFinalPos().x))
		{
			if (fLen < fScale)
			{
				Vec2 vPlayerPos = pPlayer->GetPos();
				vPlayerPos.x -= (fScale - fLen) + 1.f;

				pPlayer->SetPos(vPlayerPos);
				return;
			}
		}
		else
		{
			if (fLen < fScale)
			{
				Vec2 vPlayerPos = pPlayer->GetPos();
				vPlayerPos.x += (fScale - fLen) + 1.f;
				pPlayer->SetPos(vPlayerPos);
				return;
			}
		}
	}

	// x축에서 접근한다면 위쪽인지 아닌지 판단
	if ((pPlayer->GetCollider()->GetFinalPos().y < GetCollider()->GetFinalPos().y))
	{
		if (fLen < fScale)
		{
			Vec2 vPlayerPos = pPlayer->GetPos();
			vPlayerPos.y -= (fScale - fLen) + 1.f;
			pPlayer->SetPos(vPlayerPos);
			return;
		}
	}
	else
	{
		if (fLen < fScale)
		{
			Vec2 vPlayerPos = pPlayer->GetPos();
			vPlayerPos.y += (fScale - fLen) + 1.f;
			pPlayer->SetPos(vPlayerPos);
			return;
		}
	}
}

void CTile::tick()
{
	

	switch (m_Objecttype)
	{
	case OBJECT_TYPE::DEFAULT:

		//m_pTileAtlas = CResMgr::GetInst()->FindImg(L"TutorlalAtlas");
		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"Default");
		break;


	case OBJECT_TYPE::MAP:

		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"TileAtlas");
		
		break;
	case OBJECT_TYPE::OBJECT:

		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"StoneAtlas");

		break;
	case OBJECT_TYPE::FIRE:
		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"BonfireAtlas");
		break;
	case OBJECT_TYPE::EMPTYAREA:
		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"EmptyAreaAtlas");
		break;
	case OBJECT_TYPE::IRON:
		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"StoneAtlas");
		break;
	case OBJECT_TYPE::SHARP:
		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"ShapeAtlas");
		break;
	case OBJECT_TYPE::DOOR:
		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"DoorAtlas");
		break;
	case OBJECT_TYPE::STONE:

		m_pTileAtlas = CResMgr::GetInst()->FindImg(L"StoneAtlas");

		break;
	default:
		break;
	}

	CObject::tick();
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileAtlas || m_iImgidx == -1)
		return;

	/*if (m_Objecttype == OBJECT_TYPE::DEFAULT)
		return;*/


	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 iRevicePos;

	tSelectPen pen(_dc, PEN_COLOR::GREEN);
	tSelectBrush Brush(_dc, BRUSH_COLOR::HOLLOW);

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	int iRow = m_iImgidx / iMaxCol;
	int iCol = m_iImgidx % iMaxCol;

	/*BLENDFUNCTION tFunc1 = {};
	tFunc1.BlendOp = AC_SRC_OVER;
	tFunc1.BlendFlags = 0;
	tFunc1.AlphaFormat = AC_SRC_ALPHA;
	tFunc1.SourceConstantAlpha = 255;*/

	if (iMaxRow <= iRow)
	{
		return;
	}
	

	switch (m_Objecttype)
	{
	case OBJECT_TYPE::MAP:


		iMaxCol = m_pTileAtlas->GetWidth() / 1280;
		iMaxRow = m_pTileAtlas->GetHeight() / 720;

		iRow = m_iImgidx / iMaxCol;
		iCol = m_iImgidx % iMaxCol;

		if (iMaxCol * iMaxRow <= m_iImgidx)
		{
			m_iImgidx = 0;
		}



		TransparentBlt(_dc
			, (int)vRenderPos.x, (int)vRenderPos.y
			, 1280, 720
			, m_pTileAtlas->GetDC()
			, 1280 * iCol, 720 * iRow
			, 1280, 720
			, RGB(255, 0, 255));
		break;
	case OBJECT_TYPE::OBJECT:
		
		Typerender(_dc);


		
		break;
	case OBJECT_TYPE::FIRE:

		Typerender(_dc);

		break;
	case OBJECT_TYPE::EMPTYAREA:

		if (nullptr == m_pTileAtlas || m_iImgidx == -1)
			return;

		

		 iMaxCol = m_pTileAtlas->GetWidth() / 26;
		 iMaxRow = m_pTileAtlas->GetHeight() / 25.6f;

		 iRow = m_iImgidx / iMaxCol;
		 iCol = m_iImgidx % iMaxCol;

		vRenderPos.x += 63;
		vRenderPos.y += 48;

		if (iMaxCol * iMaxRow <= m_iImgidx)
		{
			m_iImgidx = 0;
		}


		/*AlphaBlend(_dc, (int)vRenderPos.x, (int)vRenderPos.y
			, WALLW_SIZE, WALLH_SIZE
			, m_pTileAtlas->GetDC(), WALLW_SIZE * iCol, WALLH_SIZE * iRow
			, WALLW_SIZE, WALLH_SIZE, tFunc1);*/

		TransparentBlt(_dc
			, (int)vRenderPos.x, (int)vRenderPos.y
			, WALLW_SIZE , WALLH_SIZE 
			, m_pTileAtlas->GetDC()
			, 26 * iCol, (int)(25.6 * iRow)
			, 26, (int)25.6
			, RGB(255, 0, 255));

		break;
	case OBJECT_TYPE::IRON:

		Typerender(_dc);

		break;
	case OBJECT_TYPE::SHARP:

		Typerender(_dc);

		break;
	case OBJECT_TYPE::STONE:

		Typerender(_dc);

		break;

	case OBJECT_TYPE::DOOR:

		if (nullptr == m_pTileAtlas || m_iImgidx == -1)
			return;



		iMaxCol = m_pTileAtlas->GetWidth() / 64;
		iMaxRow = m_pTileAtlas->GetHeight() / 51;

		iRow = m_iImgidx / iMaxCol;
		iCol = m_iImgidx % iMaxCol;

		if (iMaxCol * iMaxRow <= m_iImgidx)
		{
			m_iImgidx = 0;
		}

		
		iRevicePos.x = - 36;
		iRevicePos.y = - 40;

		if ( 1 == iCol || 5 == iCol || 9 == iCol || 13 == iCol)
		{
			iRevicePos.x = -36;
			iRevicePos.y = -34;
		}

		if (2 == iCol || 6 == iCol || 10 == iCol || 14 == iCol)
		{
			iRevicePos.x = -40;
			iRevicePos.y = -34;
		}

		if (3 == iCol || 7 == iCol || 11 == iCol || 15 == iCol)
		{
			iRevicePos.x = -32;
			iRevicePos.y = -25;
		}
		vRenderPos.x += 63;
		vRenderPos.y += 48;




		/*AlphaBlend(_dc, (int)vRenderPos.x, (int)vRenderPos.y
			, WALLW_SIZE, WALLH_SIZE
			, m_pTileAtlas->GetDC(), WALLW_SIZE * iCol, WALLH_SIZE * iRow
			, WALLW_SIZE, WALLH_SIZE, tFunc1);*/

		TransparentBlt(_dc
			, (int)(vRenderPos.x + iRevicePos.x), (int)(vRenderPos.y + iRevicePos.y)
			, WALLW_SIZE *2 , WALLH_SIZE * 2
			, m_pTileAtlas->GetDC()
			, 64 * iCol, 51 * iRow
			, 64, 51
			, RGB(255, 0, 255));

		break;

	case OBJECT_TYPE::DEFAULT:

		vRenderPos.x += 63;
		vRenderPos.y += 48;

		
		if (CSceneMgr::GetInst()->GetCurScene()->GetTileSwich())
		{
			Rectangle(_dc
				, (int)vRenderPos.x
				, (int)vRenderPos.y
				, (int)vRenderPos.x + WALLW_SIZE
				, (int)vRenderPos.y + WALLH_SIZE);
		}
	default:
		break;
	}
	CObject::render(_dc);
}

void CTile::CollisionBeginOverlap(CCollider* _pCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	Vec2 CameraPos = CCamera::GetInst()->GetLookAt();


	switch (m_Objecttype)
	{
	case OBJECT_TYPE::DEFAULT:
		break;
	case OBJECT_TYPE::MAP:
		break;
	case OBJECT_TYPE::OBJECT:
		break;
	case OBJECT_TYPE::IRON:		
		
		AddForbidden(_pCollider);

		AddForbidden1(_pCollider);
		break;
	case OBJECT_TYPE::STONE:
		AddForbidden(_pCollider);

		AddForbidden1(_pCollider);
		break;
	case OBJECT_TYPE::FIRE:
		break;
	case OBJECT_TYPE::EMPTYAREA:
		AddForbidden(_pCollider);

		AddForbidden1(_pCollider);

		break;
	case OBJECT_TYPE::SHARP:
		break;
	case OBJECT_TYPE::DOOR:

		if (nullptr == m_pTileAtlas || m_iImgidx == -1)
			return;

		if (0 == m_iImgidx || 8 == m_iImgidx)
		{
			Vec2 AddPos = pPlayer->GetPos();
			AddPos.y -= 96 + (WALLH_SIZE * 2);
			pPlayer->SetPos(AddPos);
			CameraPos.y -= 720;
			CCamera::GetInst()->SetLookAt(CameraPos);
		}
		
		if (1 == m_iImgidx || 9 == m_iImgidx)
		{
			Vec2 AddPos = pPlayer->GetPos();
			AddPos.x += 126 + (WALLW_SIZE * 2);
			pPlayer->SetPos(AddPos);
			CameraPos.x += 1280;
			CCamera::GetInst()->SetLookAt(CameraPos);
		}

		if (2 == m_iImgidx || 10 == m_iImgidx)
		{
			Vec2 AddPos = pPlayer->GetPos();
			AddPos.x -= 126 + (WALLW_SIZE * 2);
			pPlayer->SetPos(AddPos);
			CameraPos.x -= 1280;
			CCamera::GetInst()->SetLookAt(CameraPos);
		}
		if (3 == m_iImgidx || 11 == m_iImgidx)
		{
			Vec2 AddPos = pPlayer->GetPos();
			AddPos.y += 96 + (WALLH_SIZE * 2);
			pPlayer->SetPos(AddPos);
			CameraPos.y += 720;
			CCamera::GetInst()->SetLookAt(CameraPos);
		}

		break;
	case OBJECT_TYPE::END:
		break;
	default:
		break;
	}


	return;
}

void CTile::CollisionOverlap(CCollider* _pCollider)
{
	/*CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;*/
	CIsaacTear* pPlayer = dynamic_cast<CIsaacTear*>(_pCollider->GetOwner());

	switch (m_Objecttype)
	{
	case OBJECT_TYPE::DEFAULT:
		break;
	case OBJECT_TYPE::MAP:
		break;
	case OBJECT_TYPE::OBJECT:


		break;
	case OBJECT_TYPE::IRON:
		AddForbidden(_pCollider);
			
		AddForbidden1(_pCollider);
		
		break;
	case OBJECT_TYPE::STONE:

		AddForbidden(_pCollider);
		if (pPlayer == dynamic_cast<CIsaacTear*>(_pCollider->GetOwner()))
			return;
		AddForbidden1(_pCollider);
		break;
	case OBJECT_TYPE::FIRE:
		break;
	case OBJECT_TYPE::EMPTYAREA:

		AddForbidden(_pCollider);
		if (pPlayer == dynamic_cast<CIsaacTear*>(_pCollider->GetOwner()))
			return;
		AddForbidden1(_pCollider);
		break;
	case OBJECT_TYPE::SHARP:
		break;
	case OBJECT_TYPE::DOOR:
		if (4 <= m_iImgidx || 7 >= m_iImgidx)
		{
			AddForbidden(_pCollider);
		}

		break;
	case OBJECT_TYPE::END:
		break;
	default:
		break;
	}


	return;
}

void CTile::CollisionEndOverlap(CCollider* _pCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;

	m_bForbiden = true;
}














void CTile::Save(FILE* _pFile)
{
	SaveImageRef(m_pTileAtlas, _pFile);

	fwrite(&m_iImgidx, sizeof(int), 1, _pFile);
	fwrite(&m_Objecttype, sizeof(OBJECT_TYPE), 1, _pFile);
	fwrite(&m_VColliderScale, sizeof(Vec2), 1, _pFile);
	fwrite(&m_VColliderOffset, sizeof(Vec2), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	LoadImageRef(&m_pTileAtlas, _pFile);

	fread(&m_iImgidx, sizeof(int), 1, _pFile);
	fread(&m_Objecttype, sizeof(OBJECT_TYPE), 1, _pFile);
	fread(&m_VColliderScale, sizeof(Vec2), 1, _pFile);
	fread(&m_VColliderOffset, sizeof(Vec2), 1, _pFile);

}




