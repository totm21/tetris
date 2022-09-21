
#ifndef _WIN_ME_
#define _WIN_ME_

/*
    主窗口绘制
    @auther:    程智
    @date:      2022.8.21
*/

#include<iostream>
#include<windows.h>
#include<string>

#include"../../resources/resources.h"

class Win
{
    private:
        WNDCLASS wndclass;
        HWND hwnd;
        MSG msg;
        HDC hdc;        //dc
        HPEN pen;       //画笔
        HBRUSH hbrush;  //画刷
    public:
        Win();
        Win(HINSTANCE hInstance);
        ~Win();
        //注册窗口类
        void register_class(); 
        //创建窗口
        void create_window(LPCTSTR name,int location_x,int location_y,int width,int high);    
        //显示窗口
        void show_window();      
        //更新窗口
        void update_window();     
        //消息循环
        bool loop_message();
        //创建控制台窗口
        void create_console();
       
        //总
        void start_win(LPCTSTR name,int location_x,int location_y,int width,int high);


        //画笔部分
        void creat_pen(int type,int pixel,COLORREF color);
        //画点
        void draw_pixel(int x,int y);
};

//程序内默认窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//按键处理函数
void handle_key(WPARAM wParam,LPARAM lParam);



#endif