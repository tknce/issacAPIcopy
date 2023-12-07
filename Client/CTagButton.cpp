#include "pch.h"
#include "CTagButton.h"

#include "CImage.h"
#include "CResMgr.h"






CTagButton::CTagButton()
	: m_pFuncPointer(nullptr)
	
	, m_pNextPreButtenAtlas(nullptr)
	, m_iImgIdx(0)
{

	m_pNextPreButtenAtlas = CResMgr::GetInst()->LoadImg(L"ButtonAtlas", L"image\\isaac\\Button\\ButtonAtlas.bmp");
}

CTagButton::~CTagButton()
{
}



void CTagButton::tick()
{
	CUI::tick();
}

void CTagButton::render(HDC _dc)
{
	

	Vec2 vFinalPos = GetFinalPos();



	int iMaxCol = m_pNextPreButtenAtlas->GetWidth() / 220;
	int iMaxRow = m_pNextPreButtenAtlas->GetHeight() / 110;

	int iRow = m_iImgIdx / iMaxCol;
	int iCol = m_iImgIdx % iMaxCol;

	if (iMaxRow < iRow)
	{
		return;
	}

	TransparentBlt(
		_dc
		, (int)(vFinalPos.x), (int)(vFinalPos.y)
		, (int)GetScale().x, (int)GetScale().y
		, m_pNextPreButtenAtlas->GetDC()
		, 220 * iCol, 100 * iRow
		, 220, 100
		, RGB(255, 0, 255)
	);
	CUI::render(_dc);

	
	
}

void CTagButton::LBtnClicked()
{
	if (nullptr != m_pFuncPointer)
		m_pFuncPointer();

	if (m_Delegate.IsValid())
	{
		(m_Delegate.pInst->*m_Delegate.pFunc)();
	}

	if (m_Delegate1.isValid())
	{
		(m_Delegate1.pInst->*m_Delegate1.pFunc)(m_Delegate1.pPtr);
	}


}

