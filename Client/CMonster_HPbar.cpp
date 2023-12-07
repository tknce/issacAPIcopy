#include "pch.h"
#include "CMonster_HPbar.h"

#include "CImage.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

static int a = 0;

CMonster_HPbar::CMonster_HPbar()
	: m_CMonster_HPbar(nullptr)
	, m_fMonster_rate(1)
	, m_iHeigth(32)
{
	m_CMonster_HPbar = CResMgr::GetInst()->LoadImg(L"Monster_bar", L"image\\isaac\\UI\\Monster_bar.bmp");
}

CMonster_HPbar::~CMonster_HPbar()
{
}


void CMonster_HPbar::tick()
{
	if (m_fMonster_rate <= 0)
		DeleteObject(this);
	CObject::tick();
}

void CMonster_HPbar::render(HDC _dc)
{
	Vec2 Pos = GetPos();

	if(m_iHeigth == 32)
		TransparentBlt(_dc, Pos.x - 44, Pos.y, 500 , 100, m_CMonster_HPbar->GetDC(), 0, m_iHeigth, 150, 32, RGB(255, 0, 255));
	else
	{
		TransparentBlt(_dc, Pos.x -44 +  490  , Pos.y + 50, 495 * m_fMonster_rate, 100, m_CMonster_HPbar->GetDC(), 0, m_iHeigth, 150 * m_fMonster_rate, 31, RGB(255, 0, 255));
	}
		

	
	

	CObject::render(_dc);
}

