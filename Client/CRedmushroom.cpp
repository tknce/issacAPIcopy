#include "pch.h"
#include "CRedmushroom.h"

#include "CAnimator.h"
#include "CImage.h"
#include "CResMgr.h"

#include "CProp.h"

CRedmushroom::CRedmushroom()

{
	AddComponent(new CAnimator);

	CImage* m_ItemImage = CItem::GetImg();
	m_ItemImage = CResMgr::GetInst()->LoadImg(L"Mushroom", L"image\\isaac\\Item\\Mushroom.bmp");

	CItem::SetItemType(ITEM_TYPE::REDMUSHROOM);

	GetAnimator()->CreateAnimation(L"Mushroom", m_ItemImage, Vec2(0.f, 0.f), Vec2(32.f, 32.f), Vec2(72.f, 74.f), Vec2(0.f, 0.f), 32.f, 7, 0.2f);
	GetAnimator()->Play(L"Mushroom", true);



	

}
CRedmushroom::~CRedmushroom()
{
	
}


void CRedmushroom::tick()
{
	CObject::tick();
}



