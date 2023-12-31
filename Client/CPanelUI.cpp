#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CImage.h"

CPanelUI::CPanelUI()
	: m_PanelImage(nullptr)
{
	m_PanelImage = CResMgr::GetInst()->LoadImg(L"Panel", L"image\\isaac\\Button\\Panel.bmp");
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::tick()
{
	if (IsLBtnDown())
	{
		// 캡쳐 포지션과 현재 마우스 포지션의 차이값을 구함
		Vec2 vCurMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vMouseDiff = vCurMousePos - m_vCapturePos;
		m_vCapturePos = vCurMousePos; // 현재 마우스 위치를 캡쳐포즈로 갱신

		// 차이값 만큼 UI 포지션에 반영
		Vec2 vUIPos = GetPos();
		vUIPos += vMouseDiff;
		SetPos(vUIPos);
	}

	// 최종 위치 구함
	CUI::tick();
}

void CPanelUI::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	//tSelectPen Pen(_dc, PEN_COLOR::GREEN);
	//tSelectBrush Brush(_dc, BRUSH_COLOR::HOLLOW);

	Vec2 vFinalPos = GetFinalPos();

	/*Rectangle(_dc
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));*/

	TransparentBlt(
		_dc
		, (int)(vFinalPos.x), (int)(vFinalPos.y)
		, (int)(vScale.x), (int)( vScale.y)
		, m_PanelImage->GetDC()
		, 0, 0
		, 320, 900
		, RGB(255, 0, 255)
	);


	CUI::render(_dc);

}

void CPanelUI::LBtnDown()
{
	CUI::LBtnDown();

	m_vCapturePos = CKeyMgr::GetInst()->GetMousePos();
}

void CPanelUI::LBtnClicked()
{
	int a = 0;
}



