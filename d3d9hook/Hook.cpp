#include "pch.h"

void Hook::Patch(PBYTE dst, PBYTE src, UINT size) {
    DWORD oldProt;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProt);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldProt, &oldProt);
}

bool Hook::Detour32(void* src, void* dst, int len)
{
    if (len < 5) return false;

    DWORD curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(src, 0x90, len);

    uintptr_t relativeAddress = ((uintptr_t)dst - (uintptr_t)src) - 5;

    *(BYTE*)src = 0xE9;
    *(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(src, len, curProtection, &temp);

    return true;
}
char* Hook::TrampHook32(char* src, char* dst, const intptr_t len)
{
    // Make sure the length is greater than 5
    if (len < 5) return 0;

    // Create the gateway (len + 5 for the overwritten bytes + the jmp)
    void* gateway = VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    //Write the stolen bytes into the gateway
    memcpy(gateway, src, len);

    // Get the gateway to destination addy
    intptr_t  gatewayRelativeAddr = ((intptr_t)src - (intptr_t)gateway) - 5;

    // Add the jmp opcode to the end of the gateway
    *(char*)((intptr_t)gateway + len) = 0xE9;

    // Add the address to the jmp
    *(intptr_t*)((intptr_t)gateway + len + 1) = gatewayRelativeAddr;

    // Perform the detour
    Detour32(src, dst, len);

    return (char*)gateway;
}
Hook* hook = new Hook();