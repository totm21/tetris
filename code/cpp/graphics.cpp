
#include"graphics.h"

Graphics* graphics=new Graphics();

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
    ReleaseDC(hwnd,hdc);
}

void Graphics::init(HWND hwnd)
{
    this->hwnd=hwnd;
    this->hdc=GetDC(hwnd);
    return ;
}

void Graphics::draw_pixel(int x,int y,COLORREF color=RGB(0,0,0))
{
    SetPixel(this->hdc,x,y,color);
	return ;
}

