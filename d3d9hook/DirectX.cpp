#include "pch.h"
int wH, wW;

BOOL CALLBACK cb_enumWin(HWND handle, LPARAM lp) {
	DWORD procID;
	GetWindowThreadProcessId(handle, &procID);
	if (GetCurrentProcessId() != procID) return TRUE;
	window = handle;
	return FALSE;
}

HWND GetProcessWindow() {
	window = NULL;
	EnumWindows(cb_enumWin, NULL);
	RECT size; 
	GetWindowRect(window, &size);
	wH = size.right - size.left;
	wW = size.bottom - size.top;

	wH -= 29;
	wW -= 5;

	return window;
}
bool GetD3D9Device(PVOID* pTable, size_t size) {
	if (!pTable) return false;
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D) return false;
	IDirect3DDevice9* pDummyDevice = nullptr;
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();

	HRESULT dummyDevCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (dummyDevCreated != S_OK) {
		d3dpp.Windowed = !d3dpp.Windowed;
		HRESULT dummyDevCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
		if (dummyDevCreated != S_OK) {
			pD3D->Release();
			return false;	
		}
	}

	memcpy(pTable, *(PVOID*)pDummyDevice, size);
	pDummyDevice->Release();
	pD3D->Release();
	return true;

}