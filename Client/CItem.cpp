#include "pch.h"
#include "CItem.h"

#include "CResMgr.h"

CItem::CItem()
	: m_ItemImage(nullptr)
	, m_bItemExist(true)
	, m_Item_type()
{
	m_ItemImage = CResMgr::GetInst()->LoadImg(L"Prop", L"image\\isaac\\Map\\Item.bmp");
}

CItem::~CItem()
{
}






