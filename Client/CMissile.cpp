#include "pch.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CEventMgr.h"

CMissile::CMissile()
	: m_pImage(nullptr)
	, m_Angle(0.f)

{



}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	
	

	

	CObject::tick();
}

void CMissile::render(HDC _dc)
{	
	

	CObject::render(_dc);
}




