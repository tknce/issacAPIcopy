#include "pch.h"
#include "CDeadDEAD.h"

#include "CEnding.h"

#include "CCollider.h"


CDeadDEAD::CDeadDEAD()
{
}

CDeadDEAD::~CDeadDEAD()
{
}


void CDeadDEAD::enter()
{
	CEnding* Ending = Instantiate<CEnding>(Vec2(540.f + 1280.f, 310.f), LAYER_TYPE::ENDING);
	Ending->SetBox();
	Ending->AddComponent(new CCollider);
	Ending->GetCollider()->SetScale(Vec2(100.f, 100.f));
	Ending->GetCollider()->SetFinalPos(Vec2(590.f + 1280.f, 360.f));
	Ending->GetCollider()->SetOffset(Vec2(80.f, 50.f));

}

void CDeadDEAD::tick()
{
}

void CDeadDEAD::exit()
{
}



