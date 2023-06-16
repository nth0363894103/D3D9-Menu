#pragma once
#ifndef D_H
#define D_H
bool GetD3D9Device(PVOID* pTable, size_t size);
static HWND window;
extern int wH, wW;
extern LPDIRECT3DDEVICE9 pDevice;
#endif