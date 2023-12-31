#include "pch.h"
#include "CEngine.h"


#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CEventMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"


#include "CImage.h"
#include "Resource.h"


CEngine::CEngine()
	: m_hMainWnd(0)
	, m_hDC(0)
	, m_ptResolution{}
	, m_pBackBuffer(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
	, m_hMenu(0)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	// 펜 삭제요청
	for (UINT i = 0; i < (UINT)PEN_COLOR::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}	

	//메뉴 삭제
	DestroyMenu(m_hMenu);

}




void CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hWnd;

	m_hDC = GetDC(m_hMainWnd);

	// 윈도우 해상도 설정
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
	RECT rt = {0, 0, (LONG)_iWidth , (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	ShowWindow(m_hMainWnd, true);

	// 기본 펜 및 브러쉬 생성
	CreateDefaultGDIObject();
	CPathMgr::GetInst()->init();

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));

	// 이중 버퍼링
	// 윈도우 해상도와 동일한 크기의 비트맵을 생성
	m_pBackBuffer = CResMgr::GetInst()->CreateImg(L"Background", m_ptResolution.x, m_ptResolution.y);
	//m_pBackBuffer = CResMgr::GetInst()->LoadImg(L"Test", L"image\\Test.bmp");
	

	

	

	
	


	// Manager 초기화
	
	CPathMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();	
	CSoundMgr::GetInst()->init();
	CResMgr::GetInst()->init();

	CCamera::GetInst()->init();

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Main");
	if (nullptr != pBgm)
		pBgm->PlayToBGM(true);
	pBgm->SetVolume(20);
}

// 렌더링 관련 문제
// 1. 잔상 -> 화면 클리어
// 2. 화면 클리어 시 플레이어가 잘 안보임
// 3. 화면 갱신률과 버퍼 이미지의 전송 타이밍에 문제가 있음
// 4. 버퍼를 2개 를 사용해서 해결

void CEngine::tick()
{	
	// ======
	// Update
	// ======
	// 매니저 업데이트
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CCamera::GetInst()->tick();

	// Scene 업데이트
	CSceneMgr::GetInst()->tick(); 

	// UI 이벤트 검사
	CUIMgr::GetInst()->tick();

	// 충돌 검사
	CCollisionMgr::GetInst()->tick();


	// ======
	// 렌더링
	// ======

	

	// 버퍼 클리어 
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_pBackBuffer->GetDC(), m_arrBrush[(UINT)BRUSH_COLOR::GRAY]);
	Rectangle(m_pBackBuffer->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	SelectObject(m_pBackBuffer->GetDC(), hPrevBrush);
	
	

	//m_pBackBuffer = CResMgr::GetInst()->LoadImg(L"Test", L"image\\Test.bmp");

	// Scene Rendering
	CSceneMgr::GetInst()->render(m_pBackBuffer->GetDC());
	CTimeMgr::GetInst()->render(m_pBackBuffer->GetDC());
	CCamera::GetInst()->render(m_pBackBuffer->GetDC());
	


	//m_pBackBuffer = CResMgr::GetInst()->FindImg(L"Test");
	// BackBuffer -> MainBuffer
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pBackBuffer->GetDC(), 0, 0, SRCCOPY);
	/*TransparentBlt(m_hDC, m_ptResolution.x - m_pBackBuffer->GetWidth() 
		, (int)m_ptResolution.y - m_pBackBuffer->GetHeight() 
		, m_pBackBuffer->GetWidth(), m_pBackBuffer->GetHeight()
		, m_pBackBuffer->GetDC(), 0, 0, m_pBackBuffer->GetWidth(), m_pBackBuffer->GetHeight(), RGB(255, 0, 255));*/

	// EventMgr
	CEventMgr::GetInst()->tick();
 }

void CEngine::CreateDefaultGDIObject()
{
	// 자주 쓸 색상의 펜 생성
	m_arrPen[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 자주 쓸 Brush 생성
	m_arrBrush[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_COLOR::GRAY] = (HBRUSH)GetStockObject(GRAY_BRUSH);
}



void CEngine::SetResolution(POINT _Resolution)
{
	m_ptResolution = _Resolution;

	// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기 계산
	RECT rt = { 0, 0, (LONG)m_ptResolution.x , (LONG)m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	ShowWindow(m_hMainWnd, true);

	// 기본 펜 및 브러쉬 생성
	CreateDefaultGDIObject();
	CPathMgr::GetInst()->init();

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
}

void CEngine::AttachMenu()
{
	SetMenu(m_hMainWnd, m_hMenu);

	RECT rt = { 0, 0, m_ptResolution.x ,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);	
}

void CEngine::DetachMenu()
{
	SetMenu(m_hMainWnd, 0);

	RECT rt = { 0, 0, m_ptResolution.x ,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 크기 변경 및 Show 설정
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	ShowWindow(m_hMainWnd, true);
}