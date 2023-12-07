#pragma once

// State Pattern

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene*		m_arrScene[SCENE_TYPE::END];
	CScene*		m_pCurScene;


public:
	CScene* GetCurScene() { return m_pCurScene; }

protected:
	void ChangeScene(SCENE_TYPE _next);

public:
	void init();

	void tick();
	void render(HDC _dc);


	friend class CEventMgr;
};

