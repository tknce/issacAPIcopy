#include "pch.h"
#include "CButton.h"

#include "CImage.h"
#include "CResMgr.h"

#include "CTile.h"

CButton::CButton()
	: m_pFuncPointer(nullptr)
	, m_iImgIdx(0)
	, m_pButtenAtlas(nullptr)
	, m_ButtonType(OBJECT_TYPE::DEFAULT)
	, m_ButtonItemType(ITEM_TYPE::END)
	, m_bCollidermode(false)
{
	m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"TileAtlas");
}

CButton::~CButton()
{
}


void CButton::tick()
{
	// 버튼 타입 별 이미지 바꾸기
	switch (m_ButtonType)
	{
	case OBJECT_TYPE::MAP:

		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"TileAtlas");

		break;
	case OBJECT_TYPE::OBJECT:

		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"StoneAtlas");

		break;
	case OBJECT_TYPE::FIRE:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"BonfireAtlas");
		break;
	case OBJECT_TYPE::EMPTYAREA:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"EmptyAreaAtlas");
		break;
	case OBJECT_TYPE::IRON:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"StoneAtlas");
		break;
	case OBJECT_TYPE::SHARP:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"ShapeAtlas");
		break;
	case OBJECT_TYPE::STONE:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"StoneAtlas");

		break;

	case OBJECT_TYPE::DOOR:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"DoorAtlas");
		break;
	case OBJECT_TYPE::DEFAULT:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"Default");

		if (m_bCollidermode)
			m_pButtenAtlas = CResMgr::GetInst()->LoadImg(L"Setcollider", L"image\\isaac\\SetCollider.bmp");

		break;
	default:
		break;
	}
	switch (m_ButtonItemType)
	{
	case ITEM_TYPE::REDMUSHROOM:
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"RedMushroom");
		break;
	case ITEM_TYPE::END:
		break;
	default:
		break;
	}
	

	CUI::tick();
}

void CButton::render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();


	//// 사각형 버튼 
	///*tSelectPen Pen(_dc, PEN_COLOR::GREEN);
	//tSelectBrush Brush(_dc, BRUSH_COLOR::BLACK);*/

	Vec2 vFinalPos = GetFinalPos();

	

	int iMaxCol = m_pButtenAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pButtenAtlas->GetHeight() / TILE_SIZE;

	int iRow = m_iImgIdx / iMaxCol;
	int iCol = m_iImgIdx % iMaxCol;

	if (iMaxRow <= iRow)
	{
		return;
	}

	if (m_ButtonType == OBJECT_TYPE::MAP)
	{
		m_pButtenAtlas = CResMgr::GetInst()->FindImg(L"TileAtlas");

		iMaxCol = m_pButtenAtlas->GetWidth() / 1280;
		iMaxRow = m_pButtenAtlas->GetHeight() / 720;

		 iRow = m_iImgIdx / iMaxCol;
		 iCol = m_iImgIdx % iMaxCol;

		

		TransparentBlt(_dc
			, (int)(vFinalPos.x), (int)(vFinalPos.y)
			, (int)GetScale().x, (int)GetScale().y
			, m_pButtenAtlas->GetDC()
			, 1280 * iCol, 720 * iRow
			, 1280, 720
			, RGB(255, 0, 255));

		CUI::render(_dc);
		return;

	}
	if (m_ButtonType == OBJECT_TYPE::EMPTYAREA)
	{



		iMaxCol = m_pButtenAtlas->GetWidth() / 26;
		iMaxRow = m_pButtenAtlas->GetHeight() / 25.6f;

		iRow = m_iImgIdx / iMaxCol;
		iCol = m_iImgIdx % iMaxCol;



		/*AlphaBlend(_dc, (int)vRenderPos.x, (int)vRenderPos.y
			, WALLW_SIZE, WALLH_SIZE
			, m_pTileAtlas->GetDC(), WALLW_SIZE * iCol, WALLH_SIZE * iRow
			, WALLW_SIZE, WALLH_SIZE, tFunc1);*/

		TransparentBlt(_dc
			, (int)(vFinalPos.x), (int)(vFinalPos.y)
			, (int)GetScale().x, (int)GetScale().y
			, m_pButtenAtlas->GetDC()
			, 26 * iCol, (float)(25.6f * iRow)
			, 26, (float)(25.6f)
			, RGB(255, 0, 255));
		CUI::render(_dc);
		return;
	}
	if (m_ButtonType == OBJECT_TYPE::DOOR)
	{



		iMaxCol = m_pButtenAtlas->GetWidth() / 64;
		iMaxRow = m_pButtenAtlas->GetHeight() / 51;

		iRow = m_iImgIdx / iMaxCol;
		iCol = m_iImgIdx % iMaxCol;

		if (iMaxCol * iMaxRow <= m_iImgIdx)
		{
			m_iImgIdx = 0;
		}
		/*AlphaBlend(_dc, (int)vRenderPos.x, (int)vRenderPos.y
			, WALLW_SIZE, WALLH_SIZE
			, m_pTileAtlas->GetDC(), WALLW_SIZE * iCol, WALLH_SIZE * iRow
			, WALLW_SIZE, WALLH_SIZE, tFunc1);*/

		TransparentBlt(_dc
			, (int)(vFinalPos.x), (int)(vFinalPos.y)
			, (int)GetScale().x, (int)GetScale().y
			, m_pButtenAtlas->GetDC()
			, 64 * iCol, 51 * iRow
			, 64, 51
			, RGB(255, 0, 255));
		CUI::render(_dc);
		return;
	}
	




	TransparentBlt(
		_dc
		, (int)(vFinalPos.x), (int)(vFinalPos.y)
		, (int)GetScale().x, (int)GetScale().y
		, m_pButtenAtlas->GetDC()
		, TILE_SIZE * iCol, TILE_SIZE * iRow
		, TILE_SIZE, TILE_SIZE
		, RGB(255, 0, 255)
	);
	if (m_bCollidermode)
	{
		TransparentBlt(
			_dc
			, (int)(vFinalPos.x), (int)(vFinalPos.y)
			, (int)GetScale().x, (int)GetScale().y
			, m_pButtenAtlas->GetDC()
			, 0, 0
			, 100, 100
			, RGB(255, 0, 255)
		);
	}

	

	


	/*Rectangle(_dc
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));*/

	CUI::render(_dc);
}



void CButton::LBtnClicked()
{
	if (nullptr != m_pFuncPointer)
		m_pFuncPointer();

	if (m_Delegate.isValid())
	{
		(m_Delegate.pInst->*m_Delegate.pFunc)();
	}
	if (m_Delegate1.isValid())
	{
		(m_Delegate1.pInst->*m_Delegate1.pFunc)(m_Delegate1.pPtr);
	}
	
	
}

void CButton::AddImgIdx()
{
	++m_iImgIdx;

	int iMaxCol = m_pButtenAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pButtenAtlas->GetHeight() / TILE_SIZE;

	if (OBJECT_TYPE::MAP == m_ButtonType)
	{
		 iMaxCol = m_pButtenAtlas->GetWidth() / 1280;
		 iMaxRow = m_pButtenAtlas->GetHeight() / 720;
	}


	if (iMaxCol * iMaxRow <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}
}

void CButton::minusImgIdx()
{
	--m_iImgIdx;



	int iMaxCol = m_pButtenAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pButtenAtlas->GetHeight() / TILE_SIZE;

	if (OBJECT_TYPE::MAP == m_ButtonType)
	{
		iMaxCol = m_pButtenAtlas->GetWidth() / 1280;
		iMaxRow = m_pButtenAtlas->GetHeight() / 720;
	}

	if ( m_iImgIdx <= 0)
	{
		m_iImgIdx = iMaxCol * iMaxRow -1;
	}
}



