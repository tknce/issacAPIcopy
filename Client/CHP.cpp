#include "pch.h"
#include "CHP.h"

#include "CImage.h"
#include "CResMgr.h"

CHP::CHP()
	: m_CHP(nullptr)
	, m_IHP()
{
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP6", L"image\\isaac\\UI\\PlayerHP6.bmp");
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP5", L"image\\isaac\\UI\\PlayerHP5.bmp");
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP4", L"image\\isaac\\UI\\PlayerHP4.bmp");
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP3", L"image\\isaac\\UI\\PlayerHP3.bmp");
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP2", L"image\\isaac\\UI\\PlayerHP2.bmp");
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP1", L"image\\isaac\\UI\\PlayerHP1.bmp");
	m_CHP = CResMgr::GetInst()->LoadImg(L"PlayerHP0", L"image\\isaac\\UI\\PlayerHP0.bmp");
}

CHP::~CHP()
{
}

void CHP::tick()
{
	
	if (m_IHP == 3)
	{
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP6");
	}
	if (m_IHP == 2.5)
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP5");
	if (m_IHP == 2)
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP4");
	if (m_IHP == 1.5)
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP3");
	if (m_IHP == 1)
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP2");
	if (m_IHP == 0.5)
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP1");
	if (m_IHP == 0)
		m_CHP = CResMgr::GetInst()->FindImg(L"PlayerHP0");

	CObject::tick();
}

void CHP::render(HDC _dc)
{
	Vec2 Pos = GetPos();


	TransparentBlt(_dc, Pos.x + 50.f, Pos.y + 50.f, 135, 42, m_CHP->GetDC(),0,0,45,14,RGB(255,0,255));

	CObject::render(_dc);
}


