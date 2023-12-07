#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Logo.h"
#include "CScene_Tool.h"
#include "CScene_Start.h"
#include "CScene_Stage1.h"
#include "CStage_End.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{	
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	m_arrScene[TOOL] = new CScene_Tool;
	m_arrScene[LOGO] = new CScene_Logo;
	m_arrScene[START] = new CScene_Start;
	m_arrScene[STAGE_01] = new CScene_Stage1;
	m_arrScene[ENDING] = new CStage_End;

	ChangeScene(SCENE_TYPE::LOGO);
}

void CSceneMgr::tick()
{
	m_pCurScene->tick();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}


void CSceneMgr::ChangeScene(SCENE_TYPE _enext)
{
	if(nullptr != m_pCurScene)
	{
		m_pCurScene->exit();
	}

	m_pCurScene = m_arrScene[_enext];

	m_pCurScene->enter();
}
