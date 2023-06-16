#include "pch.h"
sHack Hack;
bool zGetAsyncKeyState(int a, int b)
{
	if (GetAsyncKeyState(a) && GetAsyncKeyState(b) || GetAsyncKeyState(b) && GetAsyncKeyState(a)) return true;
	else return false;
}
bool aGetAsyncKeyState(int a, int b, int c)
{
	if (GetAsyncKeyState(a) && GetAsyncKeyState(b) && GetAsyncKeyState(c) || GetAsyncKeyState(b) && GetAsyncKeyState(c) && GetAsyncKeyState(a) || GetAsyncKeyState(c) && GetAsyncKeyState(a) && GetAsyncKeyState(b)) return true;
	else return false;
}
void Menu::Init() {
	if (!INIT) {
		SHOW = true;				// false=hide  true=show
		INIT = true;				// STOP INITATION
	}
}

void Menu::ShowMenu()
{
	Init();
	bool chuottrai = GetAsyncKeyState(VK_LBUTTON) == -32767;
	bool chuotphai = GetAsyncKeyState(VK_RBUTTON) == -32767;
	bool left = GetAsyncKeyState(VK_LEFT)/* & 1*/ == -32767;
	bool right = GetAsyncKeyState(VK_RIGHT)/* & 1*/ == -32767;
	bool up = GetAsyncKeyState(VK_UP)/* & 1*/ == -32767;
	bool down = GetAsyncKeyState(VK_DOWN)/* & 1*/ == -32767;

	//StartWeapon();

	if (GetAsyncKeyState(VK_INSERT) /*== -32767*/ & 1) SHOW = !SHOW;

	if (SHOW)
	{
		POINT mpos;
		GetCursorPos(&mpos);// Update Mouse Coordinates
		ScreenToClient(GetForegroundWindow(), &mpos); // Translate to Current Window

#pragma region MOVE_MENU
		switch (MOVE)
		{
		default:
			break;
		case 1:
			if (!GetAsyncKeyState(VK_CONTROL)) break;
			X = (((X <= mpos.x + 4) && (X >= mpos.x)) || ((X >= mpos.x - 4) && (X <= mpos.x))) ? (X = mpos.x) : (X += ((mpos.x - X) / 4));
			Y = (((Y <= mpos.y + 4) && (Y >= mpos.y)) || ((Y >= mpos.y - 4) && (Y <= mpos.y))) ? (Y = mpos.y) : (Y += ((mpos.y - Y) / 4));
			break;
		case 2:
			if (GetAsyncKeyState(VK_UP))		Y -= 5;
			if (GetAsyncKeyState(VK_DOWN))		Y += 5;
			if (GetAsyncKeyState(VK_LEFT))		X -= 5;
			if (GetAsyncKeyState(VK_RIGHT))		X += 5;
			break;
		}
#pragma endregion
		NUM = 0;

		AddAcat("[D3D]", &Hack.ESP.main);
		AddItem("Wallhack", "[Off]|[Đỏ]|[Vàng]|[Lục]|[Lam]|[Tím]|[Trắng]", &Hack.ESP.on, Hack.ESP.main);
		AddItem("Chams", "[Off]|[Đỏ]|[Vàng]|[Lục]|[Lam]|[Tím]|[Trắng]", &Hack.ESP.on, Hack.ESP.main);
		AddItem("CrossHair", "[Off]|[Đỏ]|[Vàng]|[Lục]|[Lam]|[Tím]|[Trắng]", &Hack.ESP.on, Hack.ESP.main);
		AddItem("Color of crossHair", "[Off]|[Đỏ]|[Vàng]|[Lục]|[Lam]|[Tím]|[Trắng]", &Hack.ESP.on, Hack.ESP.main);
		

		H = (ITEM_H + 3) * NUM + 15;
		//====================================================================================================================
		//	Desc: Show Menu											
		//====================================================================================================================
		draw->DrawBox(X, Y, W, 24, C_TITTLE);											//	Hình To Màu Bên Trong
		draw->DrawBorder(X, Y, W, 24, C_BORDER);										//	Hình Viền Khung  Trên
		draw->WriteTextC(X + 10, Y + 5, Gold, DT_NOCLIP | DT_LEFT, "HACH TRUY KID");	    //	Header - Tittle
		draw->DrawBox(X, Y + 24, W, H, C_BOX);									 		//	Body - Box
		draw->DrawBorder(X, Y + 24, W, H, C_BORDER);									//	Hình Viền Khung Giữa
		draw->WriteTextA(X + 148, Y + 5, Gold, FPS(0));
		//====================================================================================================================
		//	Desc: Render												
		//====================================================================================================================
#pragma region TEXT_ON
		for (int i = 0; i < NUM; i++)
		{
			if (Item[i].Type == T_ACAT)
			{
				draw->WriteTextC(X + 10, ITEM_Y(i), C_ACAT, DT_NOCLIP | DT_LEFT, Item[i].Tittle);
				draw->WriteTextC(X + 190, ITEM_Y(i), C_ACAT, DT_NOCLIP | DT_RIGHT, Item[i].State);
			}
			if (Item[i].Type == T_ITEM)
			{
				D3DCOLOR TextColorState;
				TextColorState = (*Item[i].Variable > 0) ? C_TEXT_ON : C_TEXT_OFF;
				draw->WriteTextC(X + 10, ITEM_Y(i), TextColorState, DT_NOCLIP | DT_LEFT, Item[i].Tittle);
				TextColorState = (*Item[i].Variable > 0) ? C_ON : C_OFF;
				draw->WriteTextC(X + 190, ITEM_Y(i), TextColorState, DT_NOCLIP | DT_RIGHT, Item[i].State);
				if (i == 1)
				{
					switch (*(Item[i].Variable))
					{
					default:
						TextColorState = Red;
						break;
					case 1:
						TextColorState = Red;
						break;
					case 2:
						TextColorState = Yellow;
						break;
					case 3:
						TextColorState = Green;
						break;
					case 4:
						TextColorState = Blue;
						break;
					case 5:
						TextColorState = Purple;
						break;
					case 6:
						TextColorState = White;
						break;
					case 7:
						TextColorState = Black;
						break;
					}
				}
				//(*Item[i].Variable) > 0 ? draw->DrawBox(X + 8,ITEM_Y(i) + 2,10,10,TextColorState,pDevice) : draw->DrawBox(X + 8,ITEM_Y(i) + 2,10,10,TextColorState,pDevice);
				//draw->DrawBox(X + 10, ITEM_Y(i) + 2, 10, 10, TextColorState);
				draw->WriteTextC(X + W - 10, ITEM_Y(i), TextColorState, DT_NOCLIP | DT_RIGHT, Item[i].State);
			}
			if ((mpos.x > X) && (mpos.x < X + W))
			{
				if ((mpos.y > ITEM_Y(i)) && (mpos.y < ITEM_Y(i) + ITEM_H))
				{
					draw->DrawBorder(X + 5, ITEM_Y(i) - 1, W - 10, ITEM_H + 2, C_CURSOR);
					if (chuottrai && ((*Item[i].Variable) < (Item[i].Max - 1)))
						(*Item[i].Variable)++;
					if (chuotphai && (*Item[i].Variable > 0))
						(*Item[i].Variable)--;
				}
			}
		}
	}
}
void Menu::AddAcat(const char* Tittle, int* Variable)
{
	sprintf(Item[NUM].Tittle, Tittle);
	GetField((char*)"[ + ]|[ - ]", Item[NUM].State, *Variable + 1);
	Item[NUM].Type = T_ACAT;
	Item[NUM].Variable = Variable;
	Item[NUM].Max = 2;
	NUM++;
}

void Menu::AddItem(const char* Tittle, const char* State, int* Variable, int Main)
{
	if (Main == 1)
	{
		sprintf(Item[NUM].Tittle, Tittle);
		GetField((char*)State, Item[NUM].State, *Variable + 1);
		Item[NUM].Type = T_ITEM;
		Item[NUM].Variable = Variable;
		Item[NUM].Max = NoField((char*)State);
		NUM++;
	}
}

int Menu::NoField(char* str)
{
	TCHAR* ptr;
	int  no;
	for (no = 1; (ptr = strchr(str, L'|')) != NULL; no++)
		str = ptr + 1;
	return no;
}

void Menu::GetField(char* str, char* dst, int no)
{
	TCHAR* ptr;
	int  i;
	for (i = 1; (ptr = strchr(str, L'|')) != NULL; i++)
	{
		if (i == no) break;
		str = ptr + 1;
	}
	if (ptr)
	{
		i = (int)(ptr - str);
		strncpy(dst, str, i);
		dst[i] = 0;
	}
	else
		strcpy(dst, str);
}
#pragma endregion
#pragma region FPS
char* Menu::FPS(int en)
{
	static int	 FPScounter = 0;
	static float FPSfLastTickCount = 0.0f;
	static float FPSfCurrentTickCount;
	static char  cfps[100] = "";

	if (!en)
	{
		FPSfCurrentTickCount = clock() * 0.001f;
		FPScounter++;

		if ((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f)
		{
			FPSfLastTickCount = FPSfCurrentTickCount;
			sprintf(cfps, "   %d fps", FPScounter);
			FPScounter = 0;
		}
	}
	return cfps;
}

char* Menu::TIME(void)
{
	static char ctime[20] = "";
	struct tm* current_tm;
	time_t current_time;
	time(&current_time);
	current_tm = localtime(&current_time);
	if (current_tm->tm_hour > 12)
		sprintf(ctime, "Time: %d:%02d:%02d PM", current_tm->tm_hour - 12, current_tm->tm_min, current_tm->tm_sec);
	else
		sprintf(ctime, "Time: %d:%02d:%02d AM", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);
	return ctime;
}
Menu* menu = new Menu();
#pragma endregion