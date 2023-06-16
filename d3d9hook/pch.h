// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#pragma warning(disable : 4996)
#define _PI 3.1415926535f
// add headers that you want to pre-compile here
#include <Windows.h>
#include <cstdint>
#include <tchar.h>
#include <time.h>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <tlhelp32.h> 
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "imgui/imgui.h"
#include "imgui/dx9/imgui_impl_dx9.h"
#include "imgui/dx9/imgui_impl_win32.h"
#include "Color.h"
#include "Hook.h"
#include "DirectX.h"
#include "Draw.h"
#include "Menu.h"
#endif //PCH_H
