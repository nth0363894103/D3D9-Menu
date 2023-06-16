#pragma once
#ifndef HOOK_H
#define HOOK_H
class Hook {
public:
	void Patch(PBYTE dst, PBYTE src, UINT size);
	bool Detour32(void* src, void* dst, int len);
	char* TrampHook32(char* src, char* dst, const intptr_t len);
};
extern Hook* hook;
#endif