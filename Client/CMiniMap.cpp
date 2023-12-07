#include "pch.h"
#include "CMiniMap.h"

#include "CImage.h"
#include "CResMgr.h"

CMiniMap::CMiniMap()
	: m_CImage(nullptr)
	, m_iMinimaptype(2)
	, m_iAlpha(255)
	, m_iImagetype(0)
{
	m_CImage = CResMgr::GetInst()->LoadImg(L"MiniMap_outline", L"image\\isaac\\UI\\MiniMap_outline.bmp");
	m_CImage = CResMgr::GetInst()->LoadImg(L"MiniMap_Background", L"image\\isaac\\UI\\MiniMap_background.bmp");
	m_CImage = CResMgr::GetInst()->LoadImg(L"MiniMap", L"image\\isaac\\UI\\MiniMap.bmp");

}

CMiniMap::~CMiniMap()
{
}


void CMiniMap::tick()
{
	if (m_iMinimaptype == 1)
	{
		m_CImage = CResMgr::GetInst()->FindImg(L"MiniMap_outline");
	}
		

	if (m_iMinimaptype == 2)
		m_CImage = CResMgr::GetInst()->FindImg(L"MiniMap_Background");

	if (m_iMinimaptype == 3)
		m_CImage = CResMgr::GetInst()->FindImg(L"MiniMap");

	CObject::tick();

}

void CMiniMap::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = m_iAlpha;

	if (m_iMinimaptype == 3)
	{
		AlphaBlend(_dc
			, (int)vPos.x
			, (int)vPos.y
			, 26, 18
			, m_CImage->GetDC()
			, m_iImagetype, 0
			, 26, 18, tFunc);
	}
	else
	{
		AlphaBlend(_dc
			, (int)vPos.x
			, (int)vPos.y
			, 170, 150
			, m_CImage->GetDC()
			, 0, 0
			, 160, 120, tFunc);
	}
	

	

	//TransparentBlt(_dc, (int)vPos.x
	//	, (int)vPos.y
	//	, 500, 500
	//	, m_CImage->GetDC(), m_iImagetype, 0, 0, 0, RGB(255, 0, 255));
	CObject::render(_dc);
}


