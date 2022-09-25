
#ifndef __GRAPHICS__ME__
#define __GRAPHICS__ME__

/*
    图形绘制 
    @auther:    程智
    @date:      2022.9.25
*/


#include<windows.h>
#include"log.h"

class Dot2
{
    private:
        int x;
        int y;
    public:
        Dot2();
        Dot2(int x,int y);
        ~Dot2();
        void set_dot(int x,int y);
        void set_dot_x(int x){this->x=x;return;};
        void set_dot_y(int y){this->y=y;return;};
        int get_x(){return this->x;};
        int get_y(){return this->y;};
        bool operator <(Dot2 &dot);                 //小于号重载  基于x
        bool operator >(Dot2 &dot);                 //大于号重载  基于x
        bool operator ==(Dot2 &dot);
};

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
        void draw_pixel(int x,int y,COLORREF color=RGB(0,0,0)); //绘制像素点
        void draw_pixel(Dot2 dot,COLORREF color=RGB(0,0,0));    //绘制像素点

        //后续推出优化版 边缘渲染  但暂时先不处理
        void draw_line(int x1,int y1,int x2,int y2,bool check=false,COLORREF color=RGB(0,0,0));  //绘制线
        void draw_line(Dot2 dot1,Dot2 dot2,bool check=false,COLORREF color=RGB(0,0,0));  //绘制线

        //三角形绘制(基础版———空心)
        void draw_triangle(int x1,int y1,int x2,int y2,int x3,int y3,bool check=false,COLORREF color=RGB(0,0,0));
};

extern Graphics* graphics;

#endif
