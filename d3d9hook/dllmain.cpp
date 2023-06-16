// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
//hello world
PVOID d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LPDIRECT3DTEXTURE9 GreenTex, BlueTex;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;
tEndScene oEndScene = nullptr;
bool initialized = false;
bool g_ShowMenu = true;
bool exited = false;
static WNDPROC OriginalWndProcHandler = nullptr;
LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
    POINT mPos;
    GetCursorPos(&mPos);
    ScreenToClient(window, &mPos);
    ImGui::GetIO().MousePos.x = mPos.x;
    ImGui::GetIO().MousePos.y = mPos.y;

    if (uMsg == WM_KEYUP)
    {
        if (wParam == VK_HOME)
        {
            g_ShowMenu = !g_ShowMenu;
        }
        if (wParam == VK_END)
        {
            exited = true;
        }
    }

    if (g_ShowMenu)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        return true;
    }

    return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}
void InitImGui() {
    D3DDEVICE_CREATION_PARAMETERS CP;
    pDevice->GetCreationParameters(&CP);
    window = CP.hFocusWindow;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)hWndProc);
    io.Fonts->AddFontDefault();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
    initialized = true;
    return;
}
void UnhookImGui()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)OriginalWndProcHandler);
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    if (pDevice) {
        pDevice->Release();
    }
}
HRESULT GenerateTexture(IDirect3DDevice9* pD3Ddev, IDirect3DTexture9** ppD3Dtex, DWORD colour32)
{
    if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
        return E_FAIL;

    WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
        | (WORD)(((colour32 >> 20) & 0xF) << 8)
        | (WORD)(((colour32 >> 12) & 0xF) << 4)
        | (WORD)(((colour32 >> 4) & 0xF) << 0);

    D3DLOCKED_RECT d3dlr;
    (*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
    WORD* pDst16 = (WORD*)d3dlr.pBits;

    for (int xy = 0; xy < 8 * 8; xy++)
        *pDst16++ = colour16;

    (*ppD3Dtex)->UnlockRect(0);

    return S_OK;
}
void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 oD) {
    //GenerateTexture(pDevice, &GreenTex, D3DCOLOR_ARGB(255, 0, 255, 0));
    //GenerateTexture(pDevice, &BlueTex, D3DCOLOR_ARGB(255, 0, 0, 255));
    if (!pDevice) {
        pDevice = oD;
    }
    //draw->InitializeFont();
    //menu->ShowMenu();
    //draw->DrawBox(50, 50, 100, 100, Gold);
    if (!initialized) InitImGui();
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    if (g_ShowMenu)
    {
        bool bShow = true;
        ImGui::Begin("Hello", &bShow);
        {
            if (ImGui::Button("wall")) {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
                //pDevice->SetTexture(0, GreenTex);
                //pDrawIndexedPrimitive(pDevice, Type, BaseIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
                pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
               // pDevice->SetTexture(0, BlueTex);
            }
            if (ImGui::Button("Delete.."))
                ImGui::OpenPopup("Delete?");
            if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
                ImGui::Separator();

                //static int dummy_i = 0;
                //ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

                static bool dont_ask_me_next_time = false;
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
                ImGui::PopStyleVar();

                if (ImGui::Button("OK", ImVec2(120, 0))) { exited = true; ImGui::CloseCurrentPopup(); }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    //pDevice->SetRenderState(D3DRS_ZENABLE, true);
    draw->InitializeFont();
    menu->ShowMenu();
    oEndScene(pDevice);
}

DWORD WINAPI EntryPoint(HMODULE h) {

    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {
        memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (tEndScene)hook->TrampHook32((PCHAR)d3d9Device[42], (PCHAR)hkEndScene, 7); 
    }

    while (!exited) {
        Sleep(10);
    }
    UnhookImGui();
    hook->Patch((PBYTE)d3d9Device[42], EndSceneBytes, 7);
    FreeLibraryAndExitThread(h, 0);
}

BOOL APIENTRY DllMain( HMODULE h, DWORD r, LPVOID lpr )
{
    if (r == DLL_PROCESS_ATTACH) {
        CloseHandle(CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(EntryPoint), h, 0, 0));
    }
    return TRUE;
}

