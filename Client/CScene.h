#pragma once

#include "CEntity.h"

class CObject;


class CScene
	: public CEntity
{
private:
	vector<CObject*>	m_arrLayer[MAX_LAYER];

	UINT				m_iTileCol;
	UINT				m_iTileRow;

	UINT				m_iTileMapCol;
	UINT				m_iTileMapRow;

	bool				m_bColliderMode;
	bool				m_bTileMode;
	bool				m_bScene;
	bool				m_bDoorSound;

public:
	int					m_iMiniMapIdx;

public:
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayer) {  m_arrLayer[(UINT)_eLayer].push_back(_pObject); }
	const vector<CObject*>& GetObjects(LAYER_TYPE _eType)	{	return m_arrLayer[(UINT)_eType];	}

	void CreateTile(UINT _iCol, UINT _iRow);
	void CreateTile1(UINT _iCol, UINT _iRow, OBJECT_TYPE _objtype);
	void CreateTile2(UINT _iCol, UINT _iRow, OBJECT_TYPE _objtype, LAYER_TYPE _layer_type);
	void MiniMap();
	void Door();
	
	UINT GetTileCol() { return m_iTileCol; }	
	UINT GetTileRow() { return m_iTileRow; }
	
	UINT GetTileMapCol() { return m_iTileMapCol; }
	UINT GetTileMapRow() { return m_iTileMapRow; }

	bool GetSwich() { return m_bColliderMode; }
	void SetSwich(bool _Mode) { m_bColliderMode = _Mode; }

	bool GetTileSwich() { return m_bTileMode; }
	void SetTileSwich(bool _Mode) { m_bTileMode = _Mode; }

	void SetResoluration(LONG _x, LONG _y){
		POINT resolution;
		resolution.x = _x;
		resolution.y = _y;
		CEngine::GetInst()->SetResolution(resolution);
	}
	void SceneMove();

	void SetToolMode(bool _SceneType) { m_bScene = _SceneType; }



	

	void SetFocusedUI(CObject* _pUI);

public:

	virtual void tick();

	// Scene 진입 시 호출
	virtual void enter() = 0;


	// Scene 나올 때 호출
	virtual void exit() = 0;
	virtual void render(HDC _dc);

protected:
	void DeleteAllObject();
	void DeleteObject(LAYER_TYPE _eType);

private:
	void render_tile(HDC _dc);

public:
	CScene();
	virtual ~CScene();
};

