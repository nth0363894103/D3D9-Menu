#include "pch.h"
ID3DXLine* pLine = NULL;
LPD3DXFONT    Font;
LPD3DXFONT    font;

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};
D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v = { X, Y, Z, RHW, color };
	return v;
}

void Draw::InitializeFont() {
	bool bFont = false;
	if (Font && font)
	{
		Font->Release();
		font->Release();
		bFont = false;
	}
	if (!bFont)
	{
		D3DXCreateFontA(pDevice, 14, 6, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &Font);
		D3DXCreateFontA(pDevice, 14, 6, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
		bFont = true;
	}
}
void Draw::DrawBox(int x, int y, int w, int h, D3DCOLOR Color) {
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = {
		{ x, y + h, 0.0f, 0.0f, Color },
		{ x, y, 0.0f, 0.01, Color },
		{ x + w, y + h, 0.0f, 0.0f, Color },
		{ x + w, y, 0.0f, 0.0f, Color }
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}
void Draw::DrawBorderz(int x, int y, int w, int h, int px, D3DCOLOR BorderColors, IDirect3DDevice9* pDevice)
{
	FillRGB(x, (y + h - px), w, px, BorderColors, pDevice);
	FillRGB(x, y, px, h, BorderColors, pDevice);
	FillRGB(x, y, w, px, BorderColors, pDevice);
	FillRGB((x + w - px), y, px, h, BorderColors, pDevice);
}
void Draw::DrawBoxz(int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColors)
{
	FillRGB(x, y, w, h, BoxColor, pDevice);
	DrawBorderz(x, y, w, h, 1, BorderColors, pDevice);
}

void Draw::WriteTextC(INT x, INT y, DWORD color, DWORD Flags, CONST CHAR* text, bool isBold)
{
	RECT FontPos = { x, y, x, y };
	CHAR buf[1024] = { '\0' };

	va_list va_alist;
	va_start(va_alist, text);
	vsprintf_s(buf, text, va_alist);
	va_end(va_alist);

	if (isBold)
		Font->DrawText(NULL, buf, -1, &FontPos, Flags, color);
	else
		font->DrawText(NULL, buf, -1, &FontPos, Flags, color);
}

void Draw::WriteTextB(INT x, INT y, DWORD color, char* text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);

	int g = 1;

	RECT rect1;
	SetRect(&rect1, x + g, y, x + g, y);
	RECT rect2;
	SetRect(&rect2, x - g, y, x - g, y);
	RECT rect3;
	SetRect(&rect3, x, y + g, x, y + g);
	RECT rect4;
	SetRect(&rect4, x, y - g, x, y - g);

	Font->DrawTextA(NULL, text, -1, &rect1, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(255, 000, 000, 000));
	Font->DrawTextA(NULL, text, -1, &rect2, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(255, 000, 000, 000));
	Font->DrawTextA(NULL, text, -1, &rect3, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(255, 000, 000, 000));
	Font->DrawTextA(NULL, text, -1, &rect4, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(255, 000, 000, 000));

	Font->DrawTextA(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

void Draw::WriteTextA(INT x, INT y, DWORD color, char* text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	font->DrawTextA(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}


int Draw::GetTextWidth(CONST TCHAR* szText, LPD3DXFONT font)
{
	RECT rcRect = { 0, 0, 0, 0 };
	if (font)
	{
		font->DrawText(NULL, szText, -1, &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB(0, 0, 0));// _tclen(szText)
	}
	return rcRect.right - rcRect.left;
}

float Draw::GetTextWidths(const char* szText, LPD3DXFONT font)
{
	RECT rcRect = { 0, 0, 0, 0 };
	if (font)
	{
		font->DrawTextA(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}

	return rcRect.right - rcRect.left;
}

void Draw::DrawBorder(int x, int y, int w, int h, D3DCOLOR Color)
{
	DrawBox(x, y, 1, h, Color);
	DrawBox(x, y + h, w, 1, Color);
	DrawBox(x, y, w, 1, Color);
	DrawBox(x + w, y, 1, h + 1, Color);
	return;
}
void Draw::FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	if (w < 0)w = 1;
	if (h < 0)h = 1;
	if (x < 0)x = 1;
	if (y < 0)y = 1;

	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void Draw::DrawCircle(int x, int y, int radius, D3DCOLOR Color)
{
	const DWORD D3D_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	const int NUMPOINTS = 64;

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	float X, Y, Theta, WedgeAngle;
	WedgeAngle = (float)((2 * _PI) / NUMPOINTS);

	for (int i = 0; i <= NUMPOINTS; i++)
	{
		Theta = i * WedgeAngle;
		X = (float)(x + radius * cos(Theta));
		Y = (float)(y - radius * sin(Theta));
		Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, Color, 0.0f, 0.0f);
	}

	//pDevice->SetRenderState(D3DRS_ZENABLE, 0);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetFVF(D3D_FVF);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));
	pDevice->SetTexture(0, NULL);
}

void Draw::DrawLine(float x, float y, float x2, float y2, float width, D3DCOLOR color)
{
	if (pLine == NULL)
	{
		D3DXCreateLine(pDevice, &pLine);
	}
	D3DTLVERTEX qV[2] =
	{
		{ (float)x, (float)y, 0.0f, width, color },
		{ (float)x2, (float)y2, 0.0f, width, color },
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
}

void Draw::DrawGlosbe(int x, int y, int w, int h, D3DCOLOR Color)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	VertexSet[4] = {
		{ x, y, 0.0f, 0.0f, Color },
		{ x + 1, y, 0.0f, 0.01, Color },
		{ x + w + 1, y + h, 0.0f, 0.0f, Color },
		{ x - w, y + h, 0.0f, 0.0f, Color }
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, VertexSet, sizeof(Vertex));
	return;
}

void Draw::DrawTextBox(int x, int y, D3DCOLOR color, TCHAR* text)
{
	DrawBox(x, y, GetTextWidth(text, Font) + 10, 25, D3DCOLOR_ARGB(220, 0, 0, 0));
	DrawBorder(x, y, GetTextWidth(text, Font) + 10, 25, OrangeRed);
	WriteTextC(x + 5, y + 5, color, DT_NOCLIP | DT_LEFT, text, true);
}
Draw* draw = new Draw();