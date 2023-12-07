#include "pch.h"
#include "CEventMgr.h"


#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::tick()
{
	// Dead Object �� ������ �����Ѵ�.
	for (size_t i = 0; i < m_vecDeadObj.size(); ++i)
	{
		SAFE_DELETE(m_vecDeadObj[i]);
	}
	m_vecDeadObj.clear();


	// �̹� �����ӿ� ���� �̺�Ʈ�� ����
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		tEventInfo& evt = m_vecEvent[i];

		switch (evt.eType)
		{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			CObject* pNewObject = (CObject*)evt.first;
			LAYER_TYPE eLayer = (LAYER_TYPE)evt.second;

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			pCurScene->AddObject(pNewObject, eLayer);
		}
			break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			CObject* pDeadObj = (CObject*)evt.first;		

			if(!pDeadObj->IsDead())
			{

				m_vecDeadObj.push_back(pDeadObj);
				pDeadObj->SetDead();
			}

			
		}


			break;
		case EVENT_TYPE::SCENE_CHANGE:

			SCENE_TYPE eSceneType = (SCENE_TYPE)evt.first;

			CSceneMgr::GetInst()->ChangeScene(eSceneType);

			break;		
		}
	}

	m_vecEvent.clear();
}