
#ifndef __GRAPHICS__ME__
#define __GRAPHICS__ME__

#include<windows.h>

class Graphics
{
    private:
        HWND hwnd;
        HDC hdc;        //dc
        HPEN pen;       //画笔
        HBRUSH hbrush;  //画刷
    public:
        Graphics();
        ~Graphics();
        void init(HWND hwnd);       //初始化
        void draw_pixel(int x,int y,COLORREF color); //绘制像素点
};

extern Graphics* graphics;

#endif
