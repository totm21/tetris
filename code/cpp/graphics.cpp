
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

