
#include"graphics.h"

Graphics* graphics=new Graphics();

Dot2::Dot2()
{

}

Dot2::Dot2(int x,int y)
{
    this->x=x;
    this->y=y;
}

Dot2::~Dot2()
{

}

void Dot2::set_dot(int x,int y)
{
    this->x=x;
    this->y=y;
    return ;
}

bool Dot2::operator <(Dot2 &dot)
{
    if(this->get_x()<dot.get_x())
    {
        return true;
    }
    else if(this->get_x()==dot.get_x())
    {
        if(this->get_y()<dot.get_y())
        {
            return true;
        }
    }
    return false;
}

bool Dot2::operator >(Dot2 &dot)
{
    if(this->get_x()>dot.get_x())
    {
        return true;
    }
    else if(this->get_x()==dot.get_x())
    {
        if(this->get_y()>dot.get_y())
        {
            return true;
        }
    }
    return false;
}

bool Dot2::operator ==(Dot2 &dot)
{
    if(this->get_x()==dot.get_x()&&this->get_y()==this->get_y())
    {
        return true;
    }
    return false;
}

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

void Graphics::draw_pixel(int x,int y,COLORREF color)
{
    SetPixel(this->hdc,x,y,color);
	return ;
}

void Graphics::draw_pixel(Dot2 dot,COLORREF color)
{
    this->draw_pixel(dot.get_x(),dot.get_y(),color);
    return ;
}


void Graphics::draw_line(int x1,int y1,int x2,int y2,bool check,COLORREF color)
{
    if(check)
    {
        if(x1>x2)
        {
            int temp=x1;
            x1=x2;
            x2=temp;
            temp=y1;
            y1=y2;
            y2=temp;
        }
    }
    std::cout<<x1<<' '<<x2<<std::endl;
    double k=((double)y2-y1)/((double)x2-x1);
    double base=y1-k*x1;
    for(int i=x1;i<=x2;i++)
    {
        this->draw_pixel(i,(k*i+base)+0.5,color);
    }
    return ;
}

void Graphics::draw_line(Dot2 dot1,Dot2 dot2,bool check,COLORREF color)
{
    this->draw_line(dot1.get_x(),dot1.get_y(),dot2.get_x(),dot2.get_y(),check,color);
    return ;
}

//大体实现为连接三条线
void Graphics::draw_triangle(int x1,int y1,int x2,int y2,int x3,int y3,bool check,COLORREF color)
{
    return;
}

//从内存中渲染画面-- 0-1 ms  后面再改
void Graphics::test()
{
   COLORREF *arr = (COLORREF*) calloc(1920*1080, sizeof(COLORREF));
    /* Filling array here */
    /* ... */

    // Creating temp bitmap
    HBITMAP map = CreateBitmap(1920, // width. 512 in my case
                            1080, // height
                            1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
                            8*4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
                            (void*) arr); // pointer to array
    // Temp HDC to copy picture
    HDC src = CreateCompatibleDC(this->hdc); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
    SelectObject(src, map); // Inserting picture into our temp HDC
    // Copy image from temp HDC to window
    BitBlt(hdc, // Destination
        10,  // x and
        10,  // y - upper-left corner of place, where we'd like to copy
        1920, // width of the region
        1080, // height
        src, // source
        0,   // x and
        0,   // y of upper left corner  of part of the source, from where we'd like to copy
        SRCCOPY); // Defined DWORD to juct copy pixels. Watch more on msdn;

    DeleteDC(src); // Deleting temp HDC
    return ;
}








