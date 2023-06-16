#pragma once
#ifndef DRAW_H
#define DRAW_H

extern LPD3DXFONT    Font;
extern LPD3DXFONT    font;
class Draw {
public:
	float GetTextWidths(const char* szText, LPD3DXFONT font);
	int GetTextWidth(CONST TCHAR* szText, LPD3DXFONT font);
	void WriteTexty(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR* text);
	void DrawBoxz(int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColors);
	void DrawBorderz(int x, int y, int w, int h, int px, D3DCOLOR BorderColors, IDirect3DDevice9* pDevice);
	void InitializeFont();
	void DrawBox(int x, int y, int w, int h, D3DCOLOR Color);
	void DrawBorder(int x, int y, int w, int h, D3DCOLOR Color);
	void FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice);
	void WriteTextC(INT x, INT y, DWORD color, DWORD Flags, CONST CHAR* text, bool isBold = false);
	void WriteTextB(INT x, INT y, DWORD color, char* text);
	void WriteTextA(INT x, INT y, DWORD color, char* text);
	void DrawCircle(int x, int y, int radius, D3DCOLOR Color);
	void DrawLine(float x, float y, float x2, float y2, float width, D3DCOLOR color);
	void DrawGlosbe(int x, int y, int w, int h, D3DCOLOR Color);
	void DrawTextBox(int x, int y, D3DCOLOR color, TCHAR* text);
	void DrawCircle(int x, int y, float radius, D3DCOLOR color, IDirect3DDevice9* pDevice);
private:
	struct Vertex
	{
		float x, y, z, h;
		D3DCOLOR color;
		float tu, tv;
		static DWORD FVF;
	};
};
extern Draw* draw;
#endif