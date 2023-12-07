#pragma once


#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define IsPressed(KEY) KEY_STATE::PRESS == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsTap(KEY) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsRelease(KEY) KEY_STATE::RELEASE == CKeyMgr::GetInst()->GetKeyState(KEY)


#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;
#define CLONE(type) virtual type* Clone() override { return new type(*this);}

#define MAX_LAYER 16
#define TILE_SIZE 32
#define MAX_MAP	  32	

#define WALLH_SIZE 69
#define WALLW_SIZE 77


#define PI 3.14159265f


enum SCENE_TYPE
{
	TOOL,
	LOGO,
	START,
	STAGE_01,
	ENDING,
	END,
};

enum class PEN_COLOR
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_COLOR
{
	HOLLOW, // 투명 브러쉬
	BLACK,  // 검은 브러쉬
	GRAY,	// 회색 브러쉬
	END,
};

enum class COMPONENT_TYPE
{
	AI,
	COLLIDER,
	ANIMATOR,
	RIGIDBODY,
	END,
};



enum class LAYER_TYPE
{
	DEFAULT,
	MAP,
	BACKGROUND,
	TILE,
	PROP,
	PLAYER,
	ITEM,
	PLAYER_PROJECTILE,
	MONSTER,
	MONSTER_PROJECTILE,
	
	

	ETCUI,
	ENDING,
	UI = MAX_LAYER - 1,
	END = MAX_LAYER,
};


enum class EVENT_TYPE
{
	CREATE_OBJECT, // first : Object Adress, second : Layer Type
	DELETE_OBJECT, // first : Object Adress, 
	SCENE_CHANGE,  // first : Scene Type

	END,
};

// 타일 전용 맵에 설치된 오브젝트 판단 값
enum class OBJECT_TYPE
{
	DEFAULT,
	MAP,
	OBJECT,
	IRON,
	STONE,
	FIRE,
	EMPTYAREA,
	SHARP,
	DOOR,

	END,
};

enum class ITEM_TYPE
{
	REDMUSHROOM,
	
	
	
	
	END,
};

enum class Effect
{
	TEARM,
	TEARP,
	LIGHTCOLUMN,
	LIGHT,

	END

};