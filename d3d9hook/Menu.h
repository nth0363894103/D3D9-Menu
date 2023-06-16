#ifndef MENU_H
#define MENU_H

#define MC_MAXX					(X+WIDTH)												// X of Menu + Width
#define MC_FCTR(x,y)			((x+y)/2)												// Calculate Center Point Between two items
#define MC_ITEMY(index)			(Y+(index*I_SPC)+T_SPC+(T_SPC/2))						// Calculate Y of Item using Index or calculate Menu Maximum Y
#define MC_ITEMY1(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)-1)
#define MC_ITEMY2(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+20)
#define MC_ITEMY3(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+41)
#define MC_ITEMY4(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+60)
#define MC_ITEMY5(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+81)
#define MC_MSY					(Y+T_SPC+(T_SPC/2))
//copy
#define ITEM_MAX 64
#define ITEM_H 15											//	Item Height
#define ITEM_Y(i) (Y + 30 + (ITEM_H + 3) * i)				//	Item Y_Pos
#define TextBoxW(i) (DirectX->GetTextWidth(i, font) + 20)	//	Text Box W#e


class Menu {
public:
	Menu() {
		X = 10;
		Y = 10;
		W = 200;
		H = 0;
		Choosed = 0;
		SHOW;
	}
	enum eType
	{
		T_ITEM,	//.> 0
		T_ACAT	//.> 1
	};
	enum COLORS {  // Normal Colors
		WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
		RED = D3DCOLOR_ARGB(255, 255, 0, 0),
		GREEN = D3DCOLOR_ARGB(255, 0, 255, 0),
		BLUE = D3DCOLOR_ARGB(255, 0, 0, 255),
		BLACK = D3DCOLOR_ARGB(255, 0, 0, 0),
		PURPLE = D3DCOLOR_ARGB(255, 125, 0, 255),
		GREY = D3DCOLOR_ARGB(255, 128, 128, 128),
		YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0),
		ORANGE = D3DCOLOR_ARGB(255, 255, 125, 0)
	};

	enum eColor
	{
		C_TITTLE = D3DCOLOR_ARGB(240, 0, 0, 0),//Tên Tác Gỉa Tô Màu
		C_BOX = D3DCOLOR_ARGB(200, 0, 0, 0),//Màu Bên Trong
		C_BORDER = D3DCOLOR_ARGB(255, 255, 255, 0),//Khung Vền Ngoài

		C_ACAT = D3DCOLOR_ARGB(255, 115, 245, 110),//Màu + -

		C_TEXT_ON = D3DCOLOR_ARGB(255, 255, 215, 000),//Tên Chức Năng
		C_TEXT_OFF = D3DCOLOR_ARGB(255, 150, 150, 150),//Tên Chức Năng

		C_CURSOR = D3DCOLOR_ARGB(255, 255, 215, 000),//Khung Vền Chuột

		C_ON = D3DCOLOR_ARGB(255, 255, 215, 000),//Bật Tắt Chức Năng
		C_OFF = D3DCOLOR_ARGB(255, 150, 150, 150),//Bật Tắt Chức Năng
	};
	struct sItem
	{
		int Type;
		TCHAR Tittle[50];
		TCHAR State[50];
		int* Variable;
		int Max;
	}Item[ITEM_MAX];
	void ShowMenu();
	//.>---------------------------_VARIABLE_-------------------------------//
	int X, Y;
	int W, H;
	int NUM;
	int  WIDTH;
	int  I_SPC, I_TSPC;
	int NO;
	bool SHOW;
	bool INIT;
	int I_CUR;
	int Choosed;
	bool MOVE;
	//.>---------------------------_FUNCTION_-------------------------------//
	char* FPS(int en = 1);
	char* TIME();
	char* DATE(void);
	void	AddAcat(const char* Tittle, int* Variable);
	void	AddItem(const char* Tittle, const char* State, int* Variable, int Main);
	int		NoField(char* str);
	void	GetField(char* str, char* dst, int no);
	void	acat(char* title, char* states, int* var);
	void	aitem(char* title, char* states, int* var, int show, int when);
	void	atext(char* title, char* states, int show, int when);
	void	atext(char* title, char* states);
	void	additem(char* title, char* states, int type, int* var, int show, int when);
	void	getfield(char* str, char* dst, int no);
	int		nofields(char* str);
	void	Init(void);
	int		Load(char* szSection, char* szKey, int iDefaultValue, LPCSTR file);
	void	Save(char* szSection, char* szKey, int iValue, LPCSTR file);
};
extern Menu* menu;
struct sHack {
	struct sESP {
		int main;
		int on;
	}ESP;
};
extern sHack Hack;
#endif