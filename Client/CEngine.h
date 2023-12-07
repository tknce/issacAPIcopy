#pragma once

class CImage;

class CEngine
{
	SINGLE(CEngine);
private:
	HWND			m_hMainWnd;	// ���� ������ �ڵ�
	HDC				m_hDC;		// DC �ڵ�

	POINT			m_ptResolution; // �ػ�
	CImage*			m_pBackBuffer;	// �����(���߹��� �뵵)

	HPEN			m_arrPen[(UINT)PEN_COLOR::END];
	HBRUSH			m_arrBrush[(UINT)BRUSH_COLOR::END];

	HMENU			m_hMenu;



public:
	HWND GetMainHwnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }
	HPEN GetPen(PEN_COLOR _color) { return m_arrPen[(UINT)_color]; }
	HBRUSH GetBrush(BRUSH_COLOR _brush) { return m_arrBrush[(UINT)_brush]; }
	POINT GetResolution() { return m_ptResolution; }
	void SetResolution(POINT _Resolution);

	void AttachMenu();
	void DetachMenu();

	// �ʱ�ȭ
	void init(HWND _hWnd, UINT _iWidth, UINT _iHeight);

	// �� ������ ����
	void tick();

private:
	void CreateDefaultGDIObject();

};

