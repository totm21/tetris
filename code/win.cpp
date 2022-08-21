
#include"win.h"

win::win()
{
    this->wndclass.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));					//背景颜色画刷
	this->wndclass.hCursor = LoadCursor(NULL, IDC_HAND);								//鼠标光标类型,手：DC_HAND
	this->wndclass.hIcon = LoadIcon(NULL, IDI_ERROR);									//图标
	this->wndclass.lpszClassName = TEXT("tetris");										//窗口类型名
	this->wndclass.style = CS_HREDRAW | CS_VREDRAW;										//窗口类的风格
}