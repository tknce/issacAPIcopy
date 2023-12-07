#include "pch.h"
#include "CMonster.h"


CMonster::CMonster()
	:m_info()
{
	m_info.fDetectRange = 400.f;
	m_info.fSpeed = 200.f;
}


CMonster::~CMonster()
{
}

void CMonster::tick()
{
	CObject::tick();
}


//void CMonster::tick()
//{
//
//	//Vec2 vPos = GetPos();
//
//	//if (m_fAccTime_secon < 5) {
//	//	
//
//	//	vPos.x -= m_fSpeed*cosf(m_Angle) * DT;
//	//	vPos.y -= m_fSpeed*sinf(m_Angle) * DT;
//	//	m_fAccTime_secon += DT;
//	//	m_fAccTime += DT;
//	//	
//	//	if (m_fAccTime >= 0.4f)
//	//	{
//	//		// πÃªÁ¿œ ΩÓ±‚			
//	//		ThreeMissile();
//	//		m_fAccTime = 0.f;
//
//	//		m_Angle += PI / 6.f;
//	//	}
//
//	//}
//
//	//else if (m_fAccTime_secon < 10)
//	//{
//	//	vPos.x += m_fSpeed * DT;
//	//	m_fAccTime += DT;
//	//	if (m_fAccTime >= 0.4f)
//	//	{
//	//		// πÃªÁ¿œ ΩÓ±‚			
//	//		GreatMissile();
//	//		m_fAccTime = 0.f;
//	//		m_Angle += PI / 15.f;
//
//	//	}
//	//	
//
//	//	m_fAccTime_secon += DT;
//
//
//	//}
//
//	//else if (m_fAccTime_secon < 15) {
//
//
//	//	vPos.x += m_fSpeed * cosf(m_Angle) * DT;
//	//	vPos.y += m_fSpeed * sinf(m_Angle) * DT;
//	//	m_fAccTime_secon += DT;
//	//	m_fAccTime += DT;
//
//	//	if (m_fAccTime >= 0.4f)
//	//	{
//	//		// πÃªÁ¿œ ΩÓ±‚			
//	//		ThreeMissile();
//	//		m_fAccTime = 0.f;
//
//	//		m_Angle += PI / 6.f;
//	//	}
//
//	//}
//
//	//else if (m_fAccTime_secon < 20)
//	//{
//	//	vPos.x -= m_fSpeed * DT;
//	//	m_fAccTime += DT;
//	//	if (m_fAccTime >= 0.4f)
//	//	{
//	//		// πÃªÁ¿œ ΩÓ±‚			
//	//		GreatMissile();
//	//		m_fAccTime = 0.f;
//	//		m_Angle += PI / 15.f;
//
//	//	}
//
//
//	//	m_fAccTime_secon += DT;
//
//
//	//}
//
//	//else
//	//{
//	//	m_fAccTime_secon = 0;
//	//}
//
//	//
//
//
//	//SetPos(vPos);
//	CObject::tick();	
//
//}
//
//void CMonster::render(HDC _dc)
//{
//	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
//
//	/*TransparentBlt(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
//		, (int)vPos.y - m_pImage->GetHeight() / 2
//		, m_pImage->GetWidth(), m_pImage->GetHeight()
//		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));*/
//
//
//	BLENDFUNCTION tFunc = {};
//	tFunc.BlendOp = AC_SRC_OVER;
//	tFunc.BlendFlags = 0;	
//	tFunc.AlphaFormat = AC_SRC_ALPHA;
//	tFunc.SourceConstantAlpha = 255;
//
//	AlphaBlend(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
//		, (int)vPos.y - m_pImage->GetHeight() / 2
//		, m_pImage->GetWidth(), m_pImage->GetHeight()
//		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), tFunc);
//
//	CObject::render(_dc);
//}

//void CMonster::ThreeMissile()
//{// πÃªÁ¿œ ΩÓ±‚			
//	CMissile* pMissile = new CMissile(1);
//	pMissile->SetPos(GetPos() + Vec2(0.f, -50.f));
//
//	tEventInfo info = {};
//	info.eType = EVENT_TYPE::CREATE_OBJECT;
//	info.first = (DWORD_PTR)pMissile;
//	info.second = (DWORD_PTR)LAYER_TYPE::MONSTER_PROJECTILE;
//	pMissile->SetMissileSpeed(0, 400.f);
//	pMissile->SetAngle(1.f);
//
//	CEventMgr::GetInst()->AddEvent(info);
//
//	CMissile* pMissile1 = new CMissile(1);
//	pMissile1->SetPos(GetPos() + Vec2(0.f, -50.f));
//
//
//	info.eType = EVENT_TYPE::CREATE_OBJECT;
//	info.first = (DWORD_PTR)pMissile1;
//	info.second = (DWORD_PTR)LAYER_TYPE::MONSTER_PROJECTILE;
//	pMissile1->SetMissileSpeed(400 , 400.f );
//	pMissile1->SetAngle(PI / 4);
//
//
//	CEventMgr::GetInst()->AddEvent(info);
//
//
//	CMissile* pMissile2 = new CMissile(1);
//	pMissile2->SetPos(GetPos() + Vec2(0.f, -50.f));
//
//
//	info.eType = EVENT_TYPE::CREATE_OBJECT;
//	info.first = (DWORD_PTR)pMissile2;
//	info.second = (DWORD_PTR)LAYER_TYPE::MONSTER_PROJECTILE;
//
//
//
//	pMissile2->SetMissileSpeed(-400, 400.f );
//	pMissile2->SetAngle(PI / 4);
//
//	CEventMgr::GetInst()->AddEvent(info);
//}
//
//void CMonster::GreatMissile()
//{
//	float Angle = PI /6.f;
//
//	for (size_t i = 1; i <= 36; ++i)
//	{
//		CMissile* pMissile = new CMissile(1);
//		pMissile->SetPos(GetPos() + Vec2(0.f, -50.f));
//
//		tEventInfo info = {};
//		info.eType = EVENT_TYPE::CREATE_OBJECT;
//		info.first = (DWORD_PTR)pMissile;
//		info.second = (DWORD_PTR)LAYER_TYPE::MONSTER_PROJECTILE;
//		pMissile->SetMissileSpeed(400.f, 400.f);
//		pMissile->SetAngle(Angle);
//
//		CEventMgr::GetInst()->AddEvent(info);
//
//		Angle += PI / 12.f;
//	}
//
//	
//
//}


//void CMonster::CollisionBeginOverlap(CCollider* _pOhterCollider)
//{
//	--HP;
//	if(HP== 0)
//	{
//		tEventInfo info = {};
//		info.eType = EVENT_TYPE::DELETE_OBJECT;
//		info.first = (DWORD_PTR)this;
//		CEventMgr::GetInst()->AddEvent(info);
//	}
//	
//
//	
//	CCamera::GetInst()->ScoreUp(100);
//}



